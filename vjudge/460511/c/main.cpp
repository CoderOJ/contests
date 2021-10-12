#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1000010;
constexpr int inf = 1000000000;

struct que_t
{
  int op, l, r, h, id;
};

que_t q[N], t[N];

int f[N], val[N << 2], n, m, tt;
void build(int l = 1, int r = tt, int u = 1)
{
  val[u] = inf;
  if (l == r)
  {
    f[l] = inf;
    return;
  }
  int mid = (l + r) >> 1;
  build(l, mid, u << 1);
  build(mid + 1, r, u << 1 | 1);
}

void insert(int p, int v, int u = 1, int l = 1, int r = tt)
{
  if (l == r)
  {
    f[l] = val[u] = v;
    return;
  }
  int mid = (l + r) >> 1;
  if (p <= mid)
    insert(p, v, u << 1, l, mid);
  else
    insert(p, v, u << 1 | 1, mid + 1, r);
  val[u] = std::min(val[u << 1], val[u << 1 | 1]);
}

int pre(int p, int v, int u = 1, int l = 1, int r = tt)
{
  if (val[u] > v)
    return -1;
  if (l == r)
    return l;
  int mid = (l + r) >> 1, t = -1;
  if (p > mid)
    t = pre(p, v, u << 1 | 1, mid + 1, r);
  if (t == -1)
    t = pre(p, v, u << 1, l, mid);
  return t;
}
int suf(int p, int v, int u = 1, int l = 1, int r = tt)
{
  if (val[u] > v)
    return -1;
  if (l == r)
    return l;
  int mid = (l + r) >> 1, t = -1;
  if (p <= mid)
    t = suf(p, v, u << 1, l, mid);
  if (t == -1)
    t = suf(p, v, u << 1 | 1, mid + 1, r);
  return t;
}

int x[N], ans[N];
void init()
{
  n = sc.next_int();
  m = sc.next_int();
  tt = 0;
  for (int i = 1; i <= m; i++)
    ans[i] = -2;
  for (int i = 1; i <= m; i++)
  {
    q[i].op = sc.next_int();
    q[i].l = sc.next_int();
    q[i].r = sc.next_int();
    q[i].id = i;
    if (q[i].op == 0)
      x[++tt] = q[i].r;
    else
    {
      q[i].h = sc.next_int();
      x[++tt] = q[i].h, ans[i] = -1;
    }
  }
  std::sort(x + 1, x + tt + 1);
  tt = static_cast<int>(std::unique(x + 1, x + tt + 1) - x - 1);
  for (int i = 1; i <= m; i++)
    if (q[i].op)
      q[i].h = static_cast<int>(std::lower_bound(x + 1, x + tt + 1, q[i].h) - x);
    else
      q[i].r = static_cast<int>(std::lower_bound(x + 1, x + tt + 1, q[i].r) - x);
}

void work(int l, int r)
{
  if (l == r)
    return;
  int mid = (l + r) >> 1;
  work(l, mid);
  work(mid + 1, r);
  int pl = l, pr = mid + 1;
  auto upd = [&](int u, int p) {
    if (u == -1)
      return;
    if (ans[q[p].id] == -1 || ans[q[p].id] > abs(x[q[p].h] - x[u]))
      ans[q[p].id] = abs(x[q[p].h] - x[u]);
  };
  for (int i = l; i <= r; i++)
    if (pr > r || (pl <= mid && q[pl].l >= q[pr].l))
    {
      if (!q[pl].op && f[q[pl].r] > q[pl].l)
        insert(q[pl].r, q[pl].l);
      t[i] = q[pl++];
    }
    else
    {
      if (q[pr].op)
        upd(pre(q[pr].h, q[pr].r), pr), upd(suf(q[pr].h, q[pr].r), pr);
      t[i] = q[pr++];
    }
  for (int i = l; i <= mid; i++)
    if (!q[i].op)
      insert(q[i].r, inf);
  for (int i = l; i <= r; i++)
    q[i] = t[i];
}

void solve()
{
  build();
  work(1, m);
  for (int i = 1; i <= m; i++)
    if (ans[i] >= -1)
      printf("%d\n", ans[i]);
}

int main()
{
  int t = sc.next_int();
  while (t--)
  {
    init();
    solve();
  }
  return 0;
}
