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

constexpr int N = 405;
constexpr int K = 20;
std::vector<int> e[N];
int n, k;

int dep[N], fa[N], dr[N], dd[N], dcnt; bool ofuse[N];
void dfs1(int u, int f) {
  dep[u] = dep[f] + 1; fa[u] = f;
  for (int v: e[u]) if (v!=f) { dfs1(v, u); } }
void dfs2(int u, int f) {
  int dfn = dcnt++; dd[dfn] = dep[u];
  for (int v: e[u]) if (v!=f && ofuse[v]) { dfs2(v, u); }
  dr[dfn] = dcnt; }

bool dp[N][1 << K];
void preInit() { } void init() {
  n = sc.n(); k = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} void solve() {
  if (k > 19) { puts("DA"); return; }
  dep[0] = -1; dfs1(1,0); 
  repa (i,n) if (dep[i] == k) { int u=i; while(u) { ofuse[u] = true; u=fa[u]; } }
  dfs2(1,0); memset(dp[dcnt], 1, sizeof(dp[dcnt]));
  int state_count = 1 << k;
  repb (i,dcnt-1,1) {
    int next = dr[i], state = 1 << (dd[i] - 1);
    see(i, next, state, dd[i]);
    if (dd[i] != k) { memcpy(dp[i], dp[i+1], sizeof(dp[i+1])); }
    rep (j, state_count) if (!(j & state)) {
      dp[i][state | j] |= dp[next][j]; } 
    logArray(dp[i], dp[i]+state_count); }
  puts(dp[1][state_count - 1] ? "DA" : "NE");
}
