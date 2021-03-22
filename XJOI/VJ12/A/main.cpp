#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/dsu.h"

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
#define long long long

constexpr int N = 100005;
Temps::Vector<std::pair<int,int>> e[N];
Temps::Vector<int> ace[N];
long dp[N];
int n;

void dfs0(int u, int f) {
  for (const auto& [v,w]: e[u]) if (v != f) {
    dfs0(v,u); checkMax(dp[u], dp[v]+w); } }

void dfs1(int u, int f, long pre) {
  checkMax(dp[u], pre);
  Temps::Vector<long> best; best.resize(e[u].size());
  long pre_max = 0; int id=0;
  for (const auto& [v,w]: e[u]) if (v != f) {
    checkMax(best[id++], pre_max); checkMax(pre_max, w+dp[v]); }
  std::reverse(e[u].begin(), e[u].end());
  pre_max= 0;
  for (const auto& [v,w]: e[u]) if (v != f) {
    checkMax(best[--id], pre_max); checkMax(pre_max, w+dp[v]); }
  std::reverse(e[u].begin(), e[u].end());
  for (const auto& [v,w]: e[u]) if (v != f) {
    dfs1(v,u, std::max(pre, best[id++]) + w); } }

void dfs2(int u, int f) {
  for (const auto& [v,w]: e[u]) if (v != f) {
    ace[u].push_back(v); dfs2(v,u); } }

void preInit() { } void init() {
  n = sc.n();
  for ([[maybe_unused]] int i: range(1,n)) { 
    int u=sc.n(), v=sc.n(), w=sc.n();
    e[u].push_back({v,w}); e[v].push_back({u,w}); }
} void solve() {
  dfs0(1,0); dfs1(1,0,0);
  logArray(dp+1, dp+n+1);
  
  auto id_range = range(1,n+1);
  Temps::Vector<int> id(id_range.begin(), id_range.end());
  std::sort(id.begin(), id.end(), [](int a, int b) { return dp[a] > dp[b]; });
  dfs2(id.back(), 0);

  int q = sc.n();
  for ([[maybe_unused]] int _case: range(q)) {
    Temps::Dsu<Temps::DsuNode::NodeSize> st(n + 1);
    long thr = sc.nl(); 
    int ans=0, ld=0;
    for (int u: id) {
      while (ld < n && dp[id[ld]] - dp[u] > thr) {
        st.info(id[ld]).size--; ld++; }
      for (int v: ace[u]) { st.join(u, v); } 
      checkMax(ans, st.info(u).size); }
    printf("%d\n", ans); }
}
