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

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 1005;
int next[N], vis[N], a[N], b[N], n;
int dp[N][N];

void preInit() { 
  repa (i,N-5) {
    dp[i][0] = 0;
    repa (j, N-5) {
      if (j >= i) { checkMax(dp[i][j], dp[i][j-i] + i-1); }
      if (j > i) { checkMax(dp[i][j], dp[i][j-i-1] + i); } } }
} void init() {
  n = sc.n(); rep (i,n) a[i] = sc.n(); rep (i,n) b[i] = sc.n();
  rep (i,n) next[a[i]] = b[i];
} void solve() {
  memset(vis, 0, sizeof(vis));
  std::vector<int> loops;
  repa (i,n) if (!vis[i]) {
    int u = i; vis[u] = 1; loops.push_back(1);
    while (next[u] != i) { u = next[u]; vis[u] = 1; loops.back()++; } }
  std::sort(loops.begin(), loops.end(), [](int a, int b) { return a > b; });
  int ans = 0; rep (i,n) if (a[i] == b[i]) { ans++; }
  for (int unit=2; unit<=n; ++unit) {
    int pos = 0;
    for (std::size_t i=0; i<loops.size(); ++i) {
      if (loops[i] < unit) { break; }
      pos += dp[unit][loops[i]]; }
    checkMax(ans, pos); }
  printf("%d\n", ans);
}
