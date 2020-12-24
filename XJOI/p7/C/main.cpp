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
constexpr int B = 20;
std::vector< std::pair<int,int> > e[N];
int w[N], d[N], upw[N], n, m;

int fa[N][B];

void dfs(int u, int f) {
  fa[u][0] = f; d[u] = d[f] + 1;
  rep (b,B-1) fa[u][b+1] = fa[ fa[u][b] ][b];
  for (auto v: e[u]) if (v.first != f) {
    upw[v.first] = v.second; dfs(v.first, u); } }

void up(int& u, int d) {
  rep (i,B) if ((d>>i)&1) { u=fa[u][i]; } }
int lca(int u, int v) {
  if (d[u] < d[v]) { std::swap(u,v); } up(u, d[u]-d[v]);
  repb (i,B-1,0) if (fa[u][i] != fa[v][i]) {
    u = fa[u][i]; v = fa[v][i]; }
  return u==v ? u : fa[u][0]; } 

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  repa (i,n) w[i]=sc.n();
  rep (i,n-1) {
    int u=sc.n(), v=sc.n(), w=sc.n(); 
    e[u].push_back( std::make_pair(v,w) );
    e[v].push_back( std::make_pair(u,w) ); }
} void solve() {
  int root = 1;
  repa (i,n) if (e[i].size() == 1) { root = i; break; }
  dfs(root, 0);
  rep (i,m) {
    int u=sc.n(), v=sc.n(), l=lca(u,v);
    int pos_cost = w[u];
    long long ans = 0;
    while (u != l) {
      checkMin(pos_cost, w[u]);
      ans += 1ll * pos_cost * upw[u]; 
      u = fa[u][0]; }
    std::vector< std::pair<int, int> > vup;
    while (v != l) {
      vup.push_back( std::make_pair(w[fa[v][0]], upw[v]) );
      v = fa[v][0]; }
    std::reverse(vup.begin(), vup.end());
    for (auto p: vup) {
      checkMin(pos_cost, p.first);
      ans += 1ll * pos_cost * p.second; }
    printf("%lld\n", ans); }
}
