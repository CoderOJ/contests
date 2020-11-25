#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"

// #include "/home/jack/code/creats/STree.h"
#include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

using namespace Tree;
typedef Intm::Intm Int;
const int N = 200005;
TreeLca<N> T;

Int fac[N];

void
preInit()
{
  Int::setMod(998244353);
  fac[0] = 1;
  repa(i, N - 1) fac[i] = fac[i - 1] * Int(i);
}

Int
nCr(int n, int r)
{
  return fac[n] / fac[r] / fac[n - r];
}

void
init()
{
  int n = sc.n();
  rep(i, n - 1)
  {
    int u = sc.n(), v = sc.n();
    T.addEdge(u, v);
  }
  T.initLca(1);
}

void
solve()
{
  int q = sc.n();
  while (q--) {
    int u = sc.n(), v = sc.n();
    int l = T.lca(u, v);
    int x = T.d[u] - T.d[l], y = T.d[v] - T.d[l];
    printf("%u\n", static_cast<unsigned>(nCr(x + y, x) / Int(2).pow(x + y)));
  }
}
