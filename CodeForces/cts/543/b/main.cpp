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

constexpr int N = 3005;
std::vector<int> e[N];
int n, m, s0,t0,l0, s1,t1,l1;
int dis[N][N];

void bfs(int u) {
  int *d = dis[u]; memset(d, 0x3f, sizeof(dis[u])); d[u] = 0;
  std::queue<int> que; que.push(u);
  while (!que.empty()) {
    int u = que.front(); que.pop();
    for (int v: e[u]) if (checkMin(d[v], d[u]+1)) { que.push(v); } } }

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,m) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
  s0=sc.n(); t0=sc.n(); l0=sc.n();
  s1=sc.n(); t1=sc.n(); l1=sc.n();
} void solve() {
  repa (i,n) bfs(i);
  int ans = -1;
  repa (u,n) repa (v,n) {
    int dis_0 = dis[s0][u] + dis[u][v] + dis[v][t0];
    int dis_1 = dis[s1][u] + dis[u][v] + dis[v][t1];
    if (dis_0 <= l0 && dis_1 <= l1) {
      checkMax(ans, m - (dis[s0][u] + dis[s1][u] + dis[u][v] + dis[v][t0] + dis[v][t1])); } }
  std::swap(s1, t1);
  repa (u,n) repa (v,n) {
    int dis_0 = dis[s0][u] + dis[u][v] + dis[v][t0];
    int dis_1 = dis[s1][u] + dis[u][v] + dis[v][t1];
    if (dis_0 <= l0 && dis_1 <= l1) {
      checkMax(ans, m - (dis[s0][u] + dis[s1][u] + dis[u][v] + dis[v][t0] + dis[v][t1])); } }
  if (dis[s0][t0] <= l0 && dis[s1][t1] <= l1) {
    checkMax(ans, m - (dis[s0][t0] + dis[s1][t1])); }
  printf("%d\n", ans);
}
