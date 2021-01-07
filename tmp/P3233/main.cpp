#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

constexpr int N = 300005; 
constexpr int B = 20;
struct Tree {
  std::vector<int> e[N];
  void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); } };
struct Tree2 : public Tree {
  std::vector<int> modified; int col[N];
  void addEdge(int u, int v) { modified.push_back(u); modified.push_back(v); Tree::addEdge(u,v); }
  void clear() { for (int u: modified) { e[u].clear(); col[u] = 0; } } };

int n, q, m;
Tree T1;

int d[N], fa[N][B], sz[N], dfn[N], dfc=0;
void dfs1(int u, int f) {
  d[u] = d[f] + 1; fa[u][0] = f; sz[u] = 1; dfn[u] = dfc++; rep (b,B-1) fa[u][b+1] = fa[fa[u][b]][b];
  for (int v: T1.e[u]) if (v != f) { dfs1(v, u); sz[u] += sz[v]; } }
int up(int u, int d) { rep (i,B) if ((d>>i) & 1) { u=fa[u][i]; } return u; }
int lca(int u, int v) {
  if (d[u] < d[v]) { std::swap(u, v); } 
  { int del = d[u] - d[v]; repb (i,B-1,0) if ((del>>i) & 1) { u = fa[u][i]; } }
  repb (i,B-1,0) if (fa[u][i] != fa[v][i]) { u = fa[u][i]; v = fa[v][i]; } return u == v ? u : fa[u][0]; }

Tree2 T2;
void getVTree(std::vector<int> us) { T2.clear(); static int st[N]; int top = 0;
  std::sort(us.begin(), us.end(), [](int a, int b) { return dfn[a] < dfn[b]; });
  for (int u: us) { T2.col[u] = 1; }
  if (us.front() != 1) { us.insert(us.begin(), 1); }
  for (int u: us) { 
    while (top > 1) { int ff = st[top-2], f = st[top-1], l = lca(u, f);
      if (l == f) { break; } 
      else if (d[l] <= d[ff]) { T2.addEdge(ff, f); top--; } 
      else { T2.addEdge(l, f); st[top-1] = l; break; } }
    st[top++] = u; }
  while (top > 1) { T2.addEdge(st[top-2], st[top-1]);  top--; } }

inline auto inc(std::pair<int,int> a, int b) -> decltype(a) {
  return std::make_pair(a.first+b, a.second); }
std::pair<int, int> from[N]; int asz[N], ans[N], toUp[N];
void dfs2(int u, int f) {
  asz[u] = sz[u]; ans[u] = 0;
  for (int v: T2.e[u]) if (v != f) {
    toUp[v] = up(v, d[v] - d[u] - 1);
    asz[u] -= sz[toUp[v]]; dfs2(v, u); } }
void dfs3(int u, int f) {
  from[u] = T2.col[u] ? std::make_pair(0,u) : std::make_pair(0x3f3f3f3f,-1);
  for (int v: T2.e[u]) if (v != f) {
    dfs3(v,u); checkMin(from[u], inc(from[v],d[v] - d[u])); } }
void dfs4(int u, int f) {
  if (f) { checkMin(from[u], inc(from[f],d[u] - d[f])); }
  for (int v: T2.e[u]) if (v != f) { dfs4(v, u); } }
void dfs5(int u, int f) {
  ans[from[u].second] += asz[u];
  for (int v: T2.e[u]) if (v != f) { dfs5(v, u);
    int cnt = d[v] - d[u] - 1; if (cnt == 0) { continue; } int tou = toUp[v];
    if (from[v].second == from[u].second) { ans[from[v].second] += sz[tou] - sz[v]; }
    else { int p = v;
      repb (i, B-1, 0) { int del = (1<<i); if (del <= cnt) { int tv = fa[p][i]; 
        if (inc(from[v], d[v]-d[tv]) < inc(from[u], d[tv]-d[u])) { p = tv; } } }
      ans[from[v].second] += sz[p] - sz[v]; ans[from[u].second] += sz[tou] - sz[p]; } } }

void preInit() { } void init() {
  n = sc.n(); rep (i,n-1) { T1.addEdge(sc.n(), sc.n()); }
  dfs1(1, 0); 
} void solve() {
  q = sc.n(); while (q--) {
    int m = sc.n(); std::vector<int> us(m); rep (i,m) us[i] = sc.n();
    getVTree(us); dfs2(1,0); dfs3(1,0); dfs4(1,0); dfs5(1,0);
    for (int u: us) printf("%d ", ans[u]); puts(""); }
}
