#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

const int N = 100005;
struct Edge
{
  int u, v, w;
  bool operator<(const Edge& B) const { return w < B.w; }
} e[N];
int val[N], _v[N], p[N], n;

int
get(int u)
{
  return u == p[u] ? u : p[u] = get(p[u]);
}

void
preInit()
{}
void
init()
{
  n = sc.n();
  repa(i, n) val[i] = sc.n();
  rep(i, n - 1)
  {
    e[i].u = sc.n();
    e[i].v = sc.n();
    e[i].w = std::max(val[e[i].u], val[e[i].v]) * (n+5) + i;
  }
}
void
solve()
{
  long long ans = 0x3f3f3f3f3f3f3f3f;
  std::sort(e, e + n - 1);
  do {
    repa(i, n)
    {
      p[i] = i;
      _v[i] = val[i];
    }
    long long res = 0;
    rep(i, n-1)
    {
      int u = e[i].u, v = e[i].v;
      int pu = get(u), pv = get(v);
      res += _v[pu] + _v[pv];
      p[pv] = pu;
      checkMax(_v[pu], _v[pv]);
    }
    checkMin(ans, res);
  } while (std::next_permutation(e, e + n - 1));
  printf("%lld\n", ans);
}
