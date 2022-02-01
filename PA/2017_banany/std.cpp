#include <bits/stdc++.h>
using namespace std;
template <class T>
T read()
{
  T    s, f = 1;
  char ch;
  while (!isdigit(ch = getchar()))
    (ch == '-') && (f = -1);
  for (s = ch - '0'; isdigit(ch = getchar()); s = s * 10 + ch - '0')
    ;
  return s * f;
}
namespace cmp
{
template <class T>
bool chkmax(T &a, const T &b)
{
  return a < b ? a = b, 1 : 0;
}
template <class T>
bool chkmin(T &a, const T &b)
{
  return b < a ? a = b, 1 : 0;
}
} // namespace cmp
const int         maxn = 1e5 + 5;
const long long   inf  = 1LL << 62;
typedef long long int64;

int (*_)() = read<int>;

struct Value
{
  int64 val;
  int   id;
  Value(int64 val = 0, int id = 0) : val(val), id(id) {}
  friend bool operator<(const Value &a, const Value &b)
  {
    return a.val == b.val ? a.id > b.id : a.val < b.val;
  }
  friend Value operator+(const int64 &a, const Value &b)
  {
    return Value(b.val + a, b.id);
  }
};

struct Node
{
  Node      *ch[2], *fa;
  int64      pval, eval, sum;
  Value      lmax, rmax;
  bool       rev;
  set<Value> imax;
} pool[maxn * 2];

typedef Node *ptr;
ptr           null = &pool[0];

Node *Nodeinit(Node *p)
{
  p->ch[0] = p->ch[1] = null;
  p->fa               = null;
  p->pval = p->eval = p->sum = 0;
  p->lmax = p->rmax = Value(0, 0);
  p->rev            = 0;
  p->imax.clear();
  return p;
}

bool ntr(ptr x)
{
  return x->fa->ch[0] == x || x->fa->ch[1] == x;
}
bool getd(ptr x)
{
  return x->fa->ch[1] == x;
}
void up(ptr x)
{
  x->sum     = x->eval + x->ch[0]->sum + x->ch[1]->sum;
  Value imax = x->imax.size() ? *x->imax.rbegin() : Value(-inf, 0);
  x->lmax    = max(x->ch[0]->lmax,
                x->ch[0]->sum + max(x->eval + max(imax, x->ch[1]->lmax),
                                    Value(x->pval, x - pool)));
  x->rmax    = max(x->ch[1]->rmax,
                x->ch[1]->sum + max(x->eval + max(imax, x->ch[0]->rmax),
                                    Value(x->pval, x - pool)));
}

void r(ptr p)
{
  swap(p->ch[0], p->ch[1]);
  swap(p->lmax, p->rmax);
  p->rev ^= 1;
}

void down(ptr x)
{
  if (!x->rev)
    return;
  if (x->ch[0] != null)
    r(x->ch[0]);
  if (x->ch[1] != null)
    r(x->ch[1]);
  x->rev = 0;
}

void rot(ptr x)
{
  ptr y = x->fa, z = y->fa;
  int k = getd(x);
  ptr w = x->ch[!k];
  if (ntr(y))
    z->ch[getd(y)] = x;
  x->fa     = z;
  y->fa     = x;
  x->ch[!k] = y;
  y->ch[k]  = w;
  if (w != null)
    w->fa = y;
  up(y);
}

void splay(ptr x)
{
  static ptr st[maxn];
  int        top;
  st[top = 1] = x;
  while (ntr(st[top]))
    st[top + 1] = st[top]->fa, top++;
  while (top)
    down(st[top--]);
  for (; ntr(x); rot(x))
    if (ntr(x->fa))
      rot(getd(x->fa) == getd(x) ? x->fa : x);
  up(x);
}

void access(ptr x)
{
  for (ptr y = null; x != null; x = (y = x)->fa)
  {
    splay(x);
    if (y != null)
      x->imax.erase(y->lmax);
    if (x->ch[1] != null)
      x->imax.insert(x->ch[1]->lmax);
    x->ch[1] = y;
    up(x);
  }
}

void makeroot(ptr x)
{
  access(x);
  splay(x);
  r(x);
}

void link(ptr x, ptr f)
{
  makeroot(x);
  access(f);
  splay(f);
  x->fa = f;
  f->imax.insert(x->lmax);
  up(f);
}

unordered_map<int64, int> edge;
int64                     encode(int x, int y)
{
  if (x > y)
    swap(x, y);
  return (1LL * x) << 32 | y;
}
int n, m, q;
int main()
{
  Nodeinit(null);
  null->lmax = null->rmax = Value(-inf, n + 1);
  null->sum               = 0;
  n                       = _();
  q                       = _();
  for (int i = 1; i < n * 2; ++i)
    Nodeinit(pool + i);
  for (int i = 1; i <= n; ++i)
    pool[i].pval = read<int64>(), up(pool + i);
  for (int i = 1; i < n; ++i)
  {
    int   x = _(), y = _();
    int64 z          = read<int64>();
    pool[i + n].eval = -z;
    pool[i + n].pval = -inf;
    link(pool + x, pool + i + n);
    link(pool + y, pool + i + n);
    edge[encode(x, y)] = i;
  }
  makeroot(pool + 1);
  int nowpos = 1;
  for (int i = 1; i <= q; ++i)
  {
    int op = _();
    if (op == 1)
    {
      int   x = _();
      int64 z = read<int64>();
      access(pool + x);
      splay(pool + x);
      pool[x].pval = z;
      up(pool + x);
    }
    else
    {
      int   x = _(), y = _();
      int64 z  = read<int64>();
      int   id = edge[encode(x, y)] + n;
      access(pool + id);
      splay(pool + id);
      pool[id].eval = -z;
      up(pool + id);
    }
    access(pool + nowpos);
    splay(pool + nowpos);

    int64 tmp         = pool[nowpos].pval;
    pool[nowpos].pval = -inf;
    up(pool + nowpos);

    int ans           = pool[nowpos].lmax.id;
    pool[nowpos].pval = tmp;
    up(pool + nowpos);

    nowpos = ans;
    makeroot(pool + nowpos);
    printf("%d%c", nowpos, i == q ? '\n' : ' ');
  }
  return 0;
}
