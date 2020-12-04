#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
#include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

using namespace Tree;
const int N = 50005;
TreeLca<N> T;
std::vector< std::pair<int,int> > es[N];
int dp[N][2], n, m;

int getUp(int uu, int aa) {
  if (uu == aa) { return 0; }
  int u = uu, s = -1;
  int res = 0;
  while (u != aa) {
    res += dp[u][0];
    if (s != -1) { res -= std::max(dp[s][0], dp[s][1]); } 
    s = u; u = T.fa[u][0]; }
  res -= std::max(dp[s][0], dp[s][1]); 
  return res; }


void dfs(int u, int f) {
  dp[u][0] = dp[u][1] = 0;
  auto vs = T.getNodes(u);
  for (int v: vs) if (v!=f) { dfs(v,u); dp[u][0] += std::max(dp[v][0], dp[v][1]); }
  for (auto p: es[u]) { checkMax(dp[u][1], dp[u][0] + getUp(p.first, u) + getUp(p.second, u) + 1); }
  see(u, dp[u][0], dp[u][1]);
}

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); T.addEdge(u,v); }
  T.initLca(1);
  rep (i,m) { int u=sc.n(), v=sc.n(); es[T.lca(u,v)].push_back( std::make_pair(u,v) ); }
} void solve() {
  dfs(1,0);
  printf("%d\n", std::max(dp[1][0], dp[1][1])) ;
}
