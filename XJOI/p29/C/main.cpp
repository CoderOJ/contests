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

constexpr int N = 1005;
struct Edge {
  int u,v,w;
  bool operator< (const Edge& B) const noexcept {
    return w > B.w; }
};

struct Dsu {
  int p[N], size[N];;
  Dsu() { rep (i,N) { p[i]=i; size[i] = 1; } }
  int find_root(int u) { 
    return u == p[u] ? u : p[u] = find_root(p[u]); }
  void link(int u, int v) {
    u = find_root(u); v = find_root(v);
    p[u] = v; size[v] += size[u]; }
} st;

int d[N][N], n;
std::vector<Edge> e;
long long ans = 0;

void preInit() { } void init() {
  n = sc.n();
  repa (i,n) repa (j,n) ans -= (d[i][j] = sc.n());
  repa (i,n) repa (j,n) e.push_back(Edge{i,j,d[i][j]});
} void solve() {
  std::sort(e.begin(), e.end());
  for (const auto& p: e) {
    int u=st.find_root(p.u), v=st.find_root(p.v), w=p.w;
    if (u != v) {
      ans += 2ll * st.size[u] * st.size[v] * w;
      st.link(u, v); } }
  printf("%lld\n", ans);

}
