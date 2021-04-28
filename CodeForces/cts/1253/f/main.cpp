#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

#include <bits/stdc++.h>


/** My code begins here **/

#define int long long

constexpr int B = 20;
constexpr int N = 200005;
struct Edge  { int u, v, w; }; std::vector<Edge> es;
std::vector<std::pair<int,int>> e[N];
int n, m, k, q;

int dis[N];
void sssp() {
  for (int i=1; i<=n; ++i) dis[i] = i <= k ? 0 : std::numeric_limits<int>::max();
  std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> que; 
  for (int i=1; i<=k; ++i) que.emplace(0, i);
  while (!que.empty()) { const auto [uw,u] = que.top(); que.pop(); if (uw != dis[u]) continue;
    for (const auto& [v,w]: e[u]) if (checkMin(dis[v], uw+w)) { que.emplace(dis[v], v); } } }

int p[N], pinit = []{ for (int i=0; i<N; ++i) { p[i] = i; } return 1; }(); int get(int u) { return u == p[u] ? u : p[u] = get(p[u]); }
int w[N], w_top, fa[N][B], dep[N], sons[N][2]; 
void dfs(int u, int f) { see(u, f); dep[u] = dep[f] + 1; fa[u][0] = f; for (int i=0; i<B-1; ++i) fa[u][i+1] = fa[ fa[u][i] ][i]; if (u > n) for (int v: sons[u]) dfs(v, u); }
int lca(int u, int v) { if (dep[u] < dep[v]) { std::swap(u,v); } int delta = dep[u] - dep[v]; 
  for (int i=0; i<B; ++i) if (delta & (1<<i)) { u = fa[u][i]; } for (int i=B-1;i>=0;i--) if (fa[u][i] != fa[v][i]) { u = fa[u][i], v = fa[v][i]; } return u==v ? u : fa[u][0]; }

signed main() {
  n = sc.n(); m = sc.n(); k = sc.n(); q = sc.n(); 
  for (int i=0; i<m; ++i) { int u=sc.n(), v=sc.n(), w=sc.n(); e[u].emplace_back(v,w); e[v].emplace_back(u,w); es.push_back({u,v,w}); }
  sssp(); for (auto& e: es) { e.w += dis[e.u] + dis[e.v]; } std::sort(es.begin(), es.end(), [](const auto& a, const auto& b) { return a.w < b.w; });
  logArray(dis+1, dis+n+1);
  w_top = n+1; for (const auto& [u,v,w] : es) {  see(u,v,w);
    int pu=get(u), pv=get(v); if (pu != pv) { sons[w_top][0] = pu, sons[w_top][1] = pv, ::w[w_top] = w; p[pu] = p[pv] = w_top; w_top++; } } dfs(w_top-1,0);
  for (int i=0; i<q; ++i) { int u=sc.n(), v=sc.n(); see(u, v, lca(u,v)); printf("%lld\n", w[lca(u,v)]); }
  return 0;
}
