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

const int N = 5005;
std::vector<int> e[N];
int n;

int dp[N][N][2], sz[N];
void dfs(int u, int f) {
  if (e[u].size() == 1) { dp[u][0][0] = dp[u][1][1] = 0; sz[u] = 1; }
  else { dp[u][0][0] = dp[u][0][1] = 0; }
  for (int v: e[u]) if (v!=f) {
    dfs(v,u);
    int tmp[N][2]; memcpy(tmp, dp[u], sizeof(tmp)); memset(dp[u], 0x3f, sizeof(dp[u]));
    for (int i=0; i<=sz[u]; ++i) for (int j=0;j<=sz[v]; ++j) {
      checkMin(dp[u][i+j][0], tmp[i][0] + std::min(dp[v][j][0], dp[v][j][1]+1));
      checkMin(dp[u][i+j][1], tmp[i][1] + std::min(dp[v][j][0]+1, dp[v][j][1])); }
    sz[u] += sz[v]; }
}

void preInit() { } void init() {
  n = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} void solve() {
  if (n == 2) { puts("1"); return; }
  int R = 1; while (e[R].size() == 1) { R++; }
  memset(dp, 0x3f, sizeof(dp)); 
  dfs(R,0); 
  see(dp[2][0][0], dp[2][1][0], dp[2][2][0], dp[2][3][0], dp[2][4][0]);
  see(dp[1][0][0], dp[1][1][0], dp[1][2][0], dp[1][3][0], dp[1][4][0], dp[1][5][0], dp[1][6][0]);
  printf("%d\n", dp[R][sz[R]/2][0]);
}
