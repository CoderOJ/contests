#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 1000000007;
typedef Intm::Intm<MOD> Int;
const int N = 100005;
const int K = 105;
std::vector<int> e[N];
Int dp[N][K][2][2];
int sz[N];
int n, k;

void dfs(int u, int f) {
  dp[u][1][1][0] = dp[u][0][0][0] = 1; sz[u] = 1;
  for (int v: e[u]) if (v != f) { dfs(v,u); 
    static Int tmp[K][2][2]; memcpy(tmp, dp[u], sizeof(tmp)); memset(dp[u], 0, sizeof(dp[u]));
    for (int i=0; i<=std::min(sz[u], k); i++) for (int j=0; j<=std::min(sz[v], k-i); ++j) {
      dp[u][i+j][0][0] += tmp[i][0][0] * dp[v][j][0][1];
      dp[u][i+j][0][1] += tmp[i][0][0] * dp[v][j][1][1] + tmp[i][0][1] * (dp[v][j][0][1] + dp[v][j][1][1]);
      dp[u][i+j][1][0] += tmp[i][1][0] * (dp[v][j][0][0] + dp[v][j][0][1]);
      dp[u][i+j][1][1] += tmp[i][1][0] * (dp[v][j][1][0] + dp[v][j][1][1]) + tmp[i][1][1] * (dp[v][j][0][0] + dp[v][j][0][1] + dp[v][j][1][0] + dp[v][j][1][1]); }
    sz[u] += sz[v]; }
}

void preInit() { } void init() {
  n = sc.n(); k = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} void solve() {
  dfs(1,0); printf("%u\n", static_cast<unsigned>(dp[1][k][0][1] + dp[1][k][1][1]));
}
