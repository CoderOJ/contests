#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 200005;
constexpr int B = 20;
std::vector<int> e[N], et[N];
int n, m, q;

std::stack<int> pending;
int dfn[N], low[N], bel[N], dfn_top = 1;
void dfs(int u, int f) {
  bool skip = true;
  dfn[u] = low[u] = dfn_top++; pending.push(u);
  for (int v: e[u]) {
    if (v == f && skip) { skip = false; continue; }
    if (!dfn[v]) dfs(v, u);
    checkMin(low[u], low[v]); }
  if (low[u] == dfn[u]) {
    bel[u] = u;
    while (pending.top() != u) {
      bel[pending.top()] = u;
      pending.pop(); }
    pending.pop(); } }

int dep[N], fa[N][B], id[N];
void dfs1(int u, int f) {
  dep[u] = dep[f] + 1; fa[u][0] = f;
  for (int i=0; i+1<B; i++) fa[u][i + 1] = fa[fa[u][i]][i];
  for (int v: et[u]) if (v != f) { id[v] = id[u]; dfs1(v, u); } }
int lca(int u, int v) {
  if (dep[u] < dep[v]) return lca(v, u);
  int delta = dep[u] - dep[v]; for (int i=0; i<B; i++) if (delta & (1 << i)) u = fa[u][i];
  for (int i=B-1; i>=0; i--) if (fa[u][i] != fa[v][i]) { u = fa[u][i]; v = fa[v][i]; }
  return u == v ? u : fa[u][0]; }

std::pair<int,int> vals[N];
void dfs2(int u, int f) {
  for (int v: et[u]) if (v != f) {
    dfs2(v, u); vals[u] += vals[v]; } }
     
void preInit() {  } 
void init() 
{
  n = sc.n(); m = sc.n(); q = sc.n();
  for (int i=0; i<m; i++) { 
    int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} 

void solve() 
{
  for (int u=1; u<=n; u++) if (!dfn[u]) dfs(u, 0);
  for (int u: range(1, n+1))
    for (int v: e[u]) if (v > u && bel[u] != bel[v]) {
      et[bel[u]].push_back(bel[v]), et[bel[v]].push_back(bel[u]); }
  for (int u=1; u<=n; u++) if (!id[u]) { id[u] = u; dfs1(u, 0); }
  for (int i=0; i<q; i++) {
    int u = bel[sc.n()], v = bel[sc.n()], l = lca(u, v);
    if (id[u] != id[v]) { see(u,v,id[u],id[v]); puts("No"); return; }
    vals[u].first++; vals[l].first--; vals[v].second++; vals[l].second--; }
  for (int u=1; u<=n; u++) if (id[u] == u) { dfs2(u, 0); }
  if (std::count_if(vals+1, vals+n+1, [](auto x) { return x.first && x.second; })) { puts("No"); }
  else { puts("Yes"); }
}
