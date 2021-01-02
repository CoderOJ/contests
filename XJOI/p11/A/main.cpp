#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 100005;
constexpr int B = 20;
std::vector<int> e[N];
struct EdgeType { int u,v,w; };
std::vector<EdgeType> ps[N];
int n, m; 

int fa[N][B], d[N], dl[N], dr[N], dcnt=0;
void dfs1(int u, int f) {
  d[u] = d[f] + 1; fa[u][0] = f; dl[u] = dcnt++;
  rep (i,B-1) fa[u][i+1] = fa[fa[u][i]][i]; 
  for (int v: e[u]) if (v!=f) { dfs1(v,u); } 
  dr[u] = dcnt++; }
int lca(int u, int v) {
  if (d[u] < d[v]) { std::swap(u,v); }
  int dd = d[u] - d[v]; rep (i,B) if ((dd>>i) & 1) { u = fa[u][i]; }
  repb (i,B-1,0) if (fa[u][i] != fa[v][i]) { u=fa[u][i]; v=fa[v][i]; }
  return u==v ? u : fa[u][0]; }

struct FTree {
  static constexpr int OFFSET = 5;
  static constexpr int M = N * 2 + OFFSET;
  int a[M];
  static inline int low(int u) { return u & (-u); }
  void modify(int p, int val) { p += OFFSET; 
    while (p < M) { a[p] += val; p += low(p); } }
  int query(int p) { p += OFFSET; int res = 0;
    while (p) { res += a[p]; p -= low(p); }
    return res; }
} ft;

int dp[N][2];
void dfs2(int u, int f) {
  for (int v: e[u]) if (v != f) { dfs2(v, u); dp[u][0] += std::max(dp[v][0], dp[v][1]); }
  for (EdgeType p: ps[u]) {
    checkMax(dp[u][1], dp[u][0] + ft.query(dl[p.u]) + ft.query(dl[p.v]) + p.w); }
  int pft = dp[u][0] - std::max(dp[u][0], dp[u][1]);
  ft.modify(dl[u], pft); ft.modify(dr[u], -pft); }

void preInit() { } void init() {
  n = sc.n(); rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); } dfs1(1,0);
  m = sc.n(); rep (i,m) { int u=sc.n(), v=sc.n(), w=sc.n(), l=lca(u,v); ps[l].push_back({u,v,w}); }
} void solve() {
  dfs2(1,0); printf("%d\n", std::max(dp[1][0], dp[1][1])); 
}
