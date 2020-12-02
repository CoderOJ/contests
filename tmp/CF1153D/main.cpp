#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
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

const int N = 300005;
std::vector<int> e[N];
int col[N], n;

int dp[N], sz[N];
void dfs(int u) {
  dp[u] = 1; sz[u] = (e[u].size()==0);
  for (int v: e[u]) { dfs(v); sz[u] += sz[v]; }
  if (col[u] == 0) { for (int v: e[u]) dp[u] += dp[v]-1; } 
  else { for (int v: e[u]) checkMax(dp[u], sz[u]-sz[v]+dp[v]); }
}

void preInit() { } void init() {
  n = sc.n();
  repa (i,n) col[i] = sc.n();
  repi (i,2,n) { e[sc.n()].push_back(i); }
} void solve() { 
  dfs(1); printf("%d\n", dp[1]);
}
