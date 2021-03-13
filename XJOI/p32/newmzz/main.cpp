#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
#define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 2005;
Temps::Vector<std::pair<int,int>> e[N];
int dp[N][N*2];
int size[N], tot[N], n, k, c, tot_w;

void dfs(int u, int f) {
  size[u] = 1; tot[u] = 0;
  std::fill(dp[u], dp[u]+k*2+1, 0);
  for (const auto& p: e[u]) if (p.first != f) {
    int v = p.first, w = p.second; dfs(v,u); tot[u] += w + tot[v];
    for (int i=std::min(k*2,size[u]); i>=0; --i) {
      for (int j=size[v]; j>0; --j) {
        checkMax(dp[u][i+j], dp[u][i] + dp[v][j] + (j % 2) * w);
        checkMax(dp[u][i+j+1], dp[u][i] + dp[v][j] + w); } } 
    size[u] += size[v]; }
}

void preInit() { } void init() {
  if (scanf("%d%d%d", &n,&k,&c) == EOF) { throw true; }
  rep (i,n) e[i].resize(0); 
  tot_w = 0;
  rep (i,n-1) { 
    int u,v,w; scanf("%d%d%d",&u,&v,&w); tot_w += w;
    e[u].push_back({v,w}); e[v].push_back({u,w}); }
} void solve() {
  dfs(0,0);
  int ans = std::numeric_limits<int>::max();
  rep (i,std::min(k*2+1, size[0] + 1)) checkMin(ans, tot_w * 2 - dp[0][i] + (i+1)/2 * c);
  printf("%d\n", ans);
}
