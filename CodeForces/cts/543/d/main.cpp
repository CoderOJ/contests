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
constexpr int N = 200005;
typedef Temps::Intm<Temps::ConstModuler<MOD>> Int;
std::vector<int> e[N];
Int dp[N], ans[N];
int n;

void dfs1(const int u, const int f) {
  dp[u] = 1;
  for (const int v: e[u]) if (v != f) {
    dfs1(v,u); dp[u] *= (dp[v] + 1); } }

void dfs2(const int u, const int f, const Int uc = 0) {
  ans[u] = dp[u] * (uc + 1);
  std::vector<Int> pre{1}, suf{1};
  for (std::size_t i=0; i<e[u].size(); ++i) if (e[u][i] != f) {
    pre.push_back(pre.back() * (dp[e[u][i]]+1)); }
  for (std::size_t i=e[u].size()-1; i<=e[u].size(); --i) if (e[u][i] != f) {
    suf.push_back(suf.back() * (dp[e[u][i]]+1)); }
  int l=0, r=suf.size()-2;
  for (std::size_t i=0; i<e[u].size(); ++i) if (e[u][i] != f) {
    dfs2(e[u][i],u, pre[l++] * suf[r--] * (uc+1)); } }

void preInit() { } void init() {
  n = sc.n(); 
  repi (i,2,n) { int u=sc.n(); e[u].push_back(i); e[i].push_back(u); }
} void solve() {
  dfs1(1,0); dfs2(1,0);
  repa (i,n) printf("%d ", static_cast<int>(ans[i]));
}
