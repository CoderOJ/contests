#include "/home/jack/code/creats/gpl.h"

// #include "/home/jack/code/creats/STree.h"
#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/log.h"
// #include "/home/jack/code/creats/loop.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

void
preInit()
{}
int n, m, Q, rt;
const int N = 1000005;
const std::pair<long long,long long> seed = std::make_pair(71, 853), mo = std::make_pair(1e9 + 7, 1e9 + 9);
std::pair<long long,long long>
operator+(const std::pair<long long,long long>& a, const std::pair<long long,long long>& b)
{
  return std::make_pair((a.first + b.first) % mo.first, (a.second + b.second) % mo.second);
}
std::pair<long long,long long>
operator*(const std::pair<long long,long long>& a, const std::pair<long long,long long>& b)
{
  return std::make_pair((a.first * b.first) % mo.first, (a.second * b.second) % mo.second);
}
std::pair<long long,long long> po[N], h[N];
void
init()
{
  n = sc.n(), m = sc.n(), Q = sc.n();
  po[0] = std::make_pair(1, 1);
  for (int i = 1; i <= n; i++)
    po[i] = po[i - 1] * seed;
}
struct edg
{
  std::pair<long long,long long> to;
  int w, nxt;
} e[N];
int head[N], cnt;
const int se = 24601, p = 1e6 - 17;
struct HashTable
{
  void add(const int a, const std::pair<long long,long long> b, const int c)
  {
    cnt++;
    e[cnt].to = b, e[cnt].w = c, e[cnt].nxt = head[a], head[a] = cnt;
  }
  void inser(const std::pair<long long,long long> a, const int b)
  {
    int tmp = (a.first * se + a.second) % p;
    add(tmp, a, b);
  }
  int query(std::pair<long long,long long> a)
  {
    int tmp = (a.first * se + a.second) % p;
    for (int i = head[tmp]; i; i = e[i].nxt)
      if (e[i].to == a)
        return e[i].w;
    return -1;
  }
} Ha;
int a[N];
struct tree
{
  int l, r;
  std::pair<long long,long long> val;
} t[N << 2];
void
pushup(int ro, int len)
{
  t[ro].val = t[ro << 1].val * po[len] + t[ro << 1 | 1].val;
}
void
build(int ro, int l, int r)
{
  t[ro].l = l, t[ro].r = r;
  if (l == r) {
    t[ro].val = std::make_pair(a[l], a[l]);
    return;
  }
  int mid = (l + r) >> 1;
  build(ro << 1, l, mid), build(ro << 1 | 1, mid + 1, r);
  pushup(ro, t[ro].r - mid);
}
void
updat(int ro, int pos, int x)
{
  if (t[ro].l == t[ro].r) {
    t[ro].val = std::make_pair(x, x);
    return;
  }
  int mid = (t[ro].l + t[ro].r) >> 1;
  pos <= mid ? updat(ro << 1, pos, x) : updat(ro << 1 | 1, pos, x);
  pushup(ro, t[ro].r - mid);
}
std::pair<long long,long long>
query(int ro, int l, int r) 
{
  if (l <= t[ro].l && t[ro].r <= r)
    return t[ro].val;
  int mid = (t[ro].l + t[ro].r) >> 1;
  if (r <= mid)
    return query(ro << 1, l, r);
  else if (l > mid)
    return query(ro << 1 | 1, l, r);
  else
    return query(ro << 1, l, r) * po[std::min(r, t[ro].r) - mid] +
           query(ro << 1 | 1, l, r);
}
int
askk(int ro, int l, int r, std::pair<long long,long long> x)
{
  if (t[ro].l == t[ro].r)
    return Ha.query(x * seed + t[ro].val);
  int mid = (t[ro].l + t[ro].r) >> 1;
  if (r <= mid)
    return askk(ro << 1, l, r, x);
  else if (l > mid)
    return askk(ro << 1 | 1, l, r, x);
  else {
    std::pair<long long,long long> hh = x * po[mid - std::max(t[ro].l, l) + 1] +
             (l <= t[ro].l ? t[ro << 1].val : query(ro, l, mid));
    int w = Ha.query(hh); 
    if (w == -1)
      return askk(ro << 1, l, r, x); 
    else                             
    {
      int tmp = askk(ro << 1 | 1, l, r, hh);
      return tmp == -1 ? w : tmp;
    }
  }
}
std::vector<int> g[N];
void
dfs(int u) 
{
  sort(g[u].begin(), g[u].end());
  int cnt = 0;
  for (int sz = g[u].size(), i = 0; i < sz; i++) {
    int v = g[u][i];
    ++cnt;
    h[v] = h[u] * seed + std::make_pair(cnt, cnt);
    dfs(v);
  }
}

void
solve()
{
  for (int i = 1; i <= n; i++) {
    int x = sc.n();
    if (!x)
      rt = i;
    else
      g[x].push_back(i);
  }
  h[rt] = std::make_pair(0, 0);
  dfs(rt);
  for (int i = 1; i <= n; i++)
    Ha.inser(h[i], i);
  for (int i = 1; i <= m; i++)
    a[i] = sc.n();
  build(1, 1, m);
  int op, x, l, r, ans;
  while (Q--) {
    op = sc.n();
    if (op == 1) {
      x = sc.n(), l = sc.n(), r = sc.n();
      ans = askk(1, l, r, h[x]);
      printf("%d\n", ans == -1 ? x : ans);
    } else {
      l = sc.n(), x = sc.n();
      updat(1, l, x);
    }
  }
}
