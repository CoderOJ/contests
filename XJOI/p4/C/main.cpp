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

constexpr int N = 100005;

struct Graph {
  int n;
  std::vector<int> e[N];
  void init(int _n) { n=_n; }
  virtual void addEdge(int u, int v) {
    e[u].push_back(v); e[v].push_back(u); }
};

struct GraphDsu : public Graph {
  int p[N];
  GraphDsu() { rep (i,N) p[i] = i; }
  int get(int u) { return u==p[u] ? u : p[u] = get(p[u]); }
  inline void merge(int u, int v) { p[get(u)] = get(v); }
  inline bool query(int u, int v) { return get(u) == get(v); } 
  virtual void addEdge(int u, int v) override final {
    if (query(u,v)) { return; }
    merge(u,v); e[u].push_back(v); e[v].push_back(u); }
};

struct GraphTcc : public Graph {
  int bel[N], dfn[N], low[N], dfn_cnt=1, bel_cnt=1;
  std::stack<int> group;
  GraphTcc() { memset(dfn, -1, sizeof(dfn)); } 
  void dfs(int u, int f) {
    dfn[u] = dfn_cnt++; low[u] = dfn[u]; group.push(u);
    bool fa_protect = true;
    for (int v: e[u]) {
      if (v == f && fa_protect) { fa_protect=false; continue; }
      if (dfn[v] == -1) { dfs(v, u); }
      checkMin(low[u], low[v]); }
    if (low[u] == dfn[u]) {
      int this_bel = bel_cnt++;
      while (group.top() != u) { 
        bel[ group.top() ] = this_bel;
        group.pop(); }
      bel[ group.top() ] = this_bel;
      group.pop(); } }
  void solve(Graph& output) {
    repa (i,n) if (dfn[i] == -1) { dfs(i,0); }
    output.init(bel_cnt - 1);
    repa (u,n) for (int v: e[u]) { output.addEdge(bel[u],bel[v]); } }
};

struct TreeS : public GraphDsu {
  static constexpr int B = 20;
  int fa[N][B], d[N];

  TreeS() { memset(fa, 0, sizeof(fa)); memset(d, 0, sizeof(d)); }
  void initLca(int u, int f = 0) {
    d[u] = d[f] + 1; fa[u][0] = f;
    for (int i = 0; i < B - 1; i++) { fa[u][i + 1] = fa[fa[u][i]][i]; }
    for (int v: e[u]) if (v != f) {
      initLca(v, u); } }
  void init() {
    repa (u,n) if (d[u] == 0) { initLca(u,0); } }
  int up(int u, int d) {
    for (int i = 0; i < B; i++) { if ((d >> i) & 1) { u = fa[u][i]; } }
    return u; }
  int lca(int u, int v) {
    if (d[u] < d[v]) { int tmp = u; u = v; v = tmp; }
    u = up(u, d[u] - d[v]);
    for (int i = B - 1; i >= 0; i--) {
      if (fa[u][i] != fa[v][i]) { u = fa[u][i]; v = fa[v][i]; } }
    return u == v ? u : fa[u][0]; }
  int dis(int u, int v) {
    if (!query(u,v)) { return -1; }
    int l = lca(u,v); return d[u] + d[v] - 2*d[l]; }
};

GraphTcc Go;
TreeS Gs;
int n, m, q;

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  Go.init(n);
  rep (i,m) { int u=sc.n(), v=sc.n(); Go.addEdge(u,v); }
  Go.solve(Gs);
} void solve() {
  Gs.init();
  q = sc.n();
  while (q--) {
    int s=sc.n(), t=sc.n(), k=sc.n();
    s = Go.bel[s]; t = Go.bel[t];
    rep (i,k) { sc.n(); sc.n(); }
    printf("%d\n", Gs.dis(s,t)); }
}
