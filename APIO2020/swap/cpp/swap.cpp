#include "swap.h"

#include <bits/stdc++.h>

template <class T> inline bool checkMin (T &a, T b) { return (a > b ? a = b, 1 : 0); }
template <class T> inline bool checkMax (T &a, T b) { return (a < b ? a = b, 1 : 0); }
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " >

constexpr int N = 100005;
constexpr int M = 300005;
constexpr int B = 20;
struct edge_t { int u, v, w; };
std::vector<edge_t> es;

int deg[N];
int p[M], max_deg[M], ecnt[M], size[M], ew[M];
int fa[M][B], dep[M], ok[M];

int get(int u) {
  return u == p[u] ? u : p[u] = get(p[u]); }

void init (int n, int m, std::vector<int> eu, std::vector<int> ev, std::vector<int> ew) {
  for (size_t i=0; i<eu.size(); ++i) {
    es.push_back({eu[i] + 1, ev[i] + 1, ew[i]}); }
  std::sort(es.begin(), es.end(), [](const auto& a, const auto& b) {
    return a.w < b.w; });

  for (int i=0; i<=n+m; ++i) 
    p[i] = i, size[i] = 1, ok[i] = -1;

  int extra_cnt = n + 1;
  for (auto [u,v,w] : es) {
    deg[u]++; deg[v]++;
    int pu = get(u), pv = get(v);
    int p = extra_cnt++; ::ew[p] = w;
    if (pu == pv) {
      fa[pu][0] = ::p[pu] = p;
      size[p] = size[pu];
      max_deg[p] = std::max({max_deg[pu], deg[u], deg[v]});
      ecnt[p] = ecnt[pu] + 1; }
    else {
      fa[pu][0] = fa[pv][0] = ::p[pu] = ::p[pv] = p;
      size[p] = size[pu] + size[pv];
      max_deg[p] = std::max({max_deg[pu], max_deg[pv], deg[u], deg[v]});
      ecnt[p] = ecnt[pu] + ecnt[pv] + 1; } }

  for (int i=extra_cnt-1; i>=1; i--) {
    dep[i] = dep[fa[i][0]] + 1; 
    ok[i] = (ecnt[i] >= size[i] || max_deg[i] > 2) ? i : ok[fa[i][0]]; }

  for (int b=0; b+1<B; ++b)
    for (int u=1; u<extra_cnt; ++u)
      fa[u][b + 1] = fa[fa[u][b]][b]; }

int lca(int u, int v) {
  if (dep[u] < dep[v]) return lca(v, u);
  int delta = dep[u] - dep[v]; for (int i=0; i<B; ++i) if (delta & (1 << i)) u = fa[u][i];
  for (int i=B-1; i>=0; i--) if (fa[u][i] != fa[v][i]) { u = fa[u][i]; v = fa[v][i]; }
  return u == v ? u : fa[u][0]; }

int getMinimumFuelCapacity (int u, int v) {
  u++, v++;
  int id = ok[lca(u, v)];
  return id != -1 ? ::ew[id] : -1; }
