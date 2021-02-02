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

constexpr int N = 2005;
std::vector<int> e[N];
int col[N], sz[N], min[N], max[N], n;

void dfs(int u, int f) {
  std::vector<std::pair<int, int>> vs;
  for (int v: e[u]) if (v != f) {
    dfs(v, u); sz[u] += sz[v]; max[u] += max[v] + sz[v];
    vs.push_back(std::make_pair(min[v] + sz[v], v)); }
  if (vs.empty()) { return; }
  // logArray(vs.begin(), vs.end());
  auto m = *std::max_element(vs.begin(), vs.end()); int oth_sum = 0;
  for (auto v: vs) if (v.second != m.second) { oth_sum += max[v.second] + sz[v.second]; }
  min[u] = m.first - oth_sum;
  if (min[u] < 0) { min[u] &= 1; } }

void preInit() { } void init() {
  n = sc.n(); repa (i,n) col[i] = sc.nextChar() == '1';
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} void solve() {
  int ans = std::numeric_limits<decltype(ans)>::max();
  repa (u, n) {
    memcpy(sz, col, sizeof(*sz) * (n + 1)); memset(min, 0, sizeof(min)); memset(max, 0, sizeof(max)); dfs(u, 0);
    if (min[u] == 0) { checkMin(ans, max[u] / 2); } }
  if (ans == std::numeric_limits<decltype(ans)>::max()) { puts("-1"); }
  else { printf("%d\n", ans); }
}
