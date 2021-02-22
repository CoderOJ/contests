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

constexpr int N = 505;
constexpr int B = 62;
std::bitset<N> vis[B][N][2];
int n, m;

long long find_route(int u, int k) {
  static long long mem[N][2];
  if (mem[u][k]) { return mem[u][k]; }
  if (!vis[0][u][k].any()) { return 0; }
  int max_b = 0;
  rep (i,B) if (!vis[i][u][k].any()) { max_b = i-1; break; }
  long long max_next = 0;
  repa (v,n) if (vis[max_b][u][k][v]) {
    checkMax(max_next, find_route(v, !k)); }
  return mem[u][k] = (1ll << max_b) + max_next; }

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,m) { int u=sc.n(), v=sc.n(), w=sc.n();
    vis[0][u][w][v] = 1; }
} void solve() {
  rep (b,B-1) rep (k,2) repa (u,n) {
    repa (v,n) if (vis[b][u][k][v]) {
      vis[b+1][u][k] |= vis[b][v][!k]; } }
  if (vis[B-1][1][0].any()) { puts("-1"); return; }
  long long ans = find_route(1,0);
  printf("%lld\n", (ans > (long long)(1e18)) ? -1ll : ans);
}
