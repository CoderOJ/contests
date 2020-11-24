#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

const int N = 3005;
std::vector<int> ind[N], oud[N];
int n, m;

void
preInit()
{}

void
init()
{
  n = sc.n();
  m = sc.n();
  rep(i, m)
  {
    int u = sc.n(), v = sc.n();
    ind[v].push_back(u);
    oud[u].push_back(v);
  }
}

int bridge[N][N];

void
solve()
{
  long long ans = 0;
  repa(i, n)
  {
    for (int u : ind[i])
      for (int v : oud[i])
        bridge[u][v]++;
    std::set <int> os;
    for (int u: oud[i])
      os.insert(u);
    int tr_cnt = 0;
    for (int u: ind[i])
      if (os.count(u))
        tr_cnt ++;
    ans -= tr_cnt * (tr_cnt-1);
  }
  repa(u, n) repa(v, n)
  {
    if (u == v)
      continue;
    ans += bridge[u][v] * bridge[v][u];
  }
  see(ans);
  printf("%lld\n", ans / 4);
}
