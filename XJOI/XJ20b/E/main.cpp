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
#define int long long

/** My code begins here **/

const int N = 405;
const int MOD = 998244353;
std::vector <int> e[N];
int n;

void preInit()
{

}

void init()
{
  n = sc.n();
  rep (i,n-1) {
    int u=sc.n(), v=sc.n();
    e[u].push_back(v); e[v].push_back(u); }
}

int cnt[N][N];
void dfs(int u, int f, int ori, int dep) {
  // see(u,f,ori,dep);
  cnt[ori][dep]++;
  for (int v: e[u]) if (v!=f) {
    dfs(v,u,ori,dep+1); } }

int ans[N];
int dp[N][N];
void solve()
{
  repa (u,n) {
    memset(cnt, 0, sizeof(cnt));
    int sz = e[u].size();
    for (int v: e[u]) { dfs(v,u,v,1); }
    for (int len=1; len<n; ++len) {
      rep (i,sz+1) { memset(dp[i], 0, sizeof(dp[i])); }
      dp[0][0] = 1;
      repa (i,sz) rep (k,i+1) {
        dp[i][k] = dp[i-1][k];
        // see(e[u][i-1], len, cnt[e[u][i-1]][len]);
        if (k) { (dp[i][k] += dp[i-1][k-1] * cnt[e[u][i-1]][len]) %= MOD; } } 
      for (int k=3; k<n; ++k) {
        (ans[k] += dp[sz][k]) %= MOD; }
    }
  }
  repi (i,3,n-1) printf("%lld\n", ans[i]);
}
