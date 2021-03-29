#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

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

constexpr int N = 15;

Temps::Vector<int> e[N];
int dis[N][N];
int n;

void dfs(int u, int f, int d, int* output) {
  output[u] = d;
  for (int v: e[u]) if (v != f) {
    dfs(v,u, d+1, output); } }

std::map<std::array<int, N>, int> dp;
int dfs2(std::array<int, N> mask, int who=1, int round=1) {
  if (dp.count(mask)) { return dp[mask]; }
  if (round > n) {
    int ans = 0;
    repa (i,n) repa (j,n) if (mask[i]==1 && mask[j]==1) checkMax(ans, dis[i][j]);
    return dp[mask] = ans; }
  if (who == 1) {
    int ans = 0x3f3f3f3f;
    repa (i,n) if (mask[i] == 0) {
      mask[i] = 1;
      checkMin(ans, dfs2(mask, 2, round+1));
      mask[i] = 0; }
    return dp[mask] = ans; }
  else {
    int ans = 0;
    repa (i,n) if (mask[i] == 0) {
      mask[i] = 2;
      checkMax(ans, dfs2(mask, 1, round+1));
      mask[i] = 0; }
    return dp[mask] = ans; } }

void preInit() { } void init() {
  n = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} void solve() {
  repa (i,n) dfs(i,0,0,dis[i]);
  printf("%d\n", dfs2(std::array<int,N>()));
}
