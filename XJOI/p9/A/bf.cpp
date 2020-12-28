#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
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
int n, m, s[N], t[N];

struct Tree {
  std::vector<int> e[N];
  int dl[N], dr[N], dc=0;
  int fa[N][B], d[N];
  void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
  void dfs(int u, int f=0) {
    d[u] = d[f] + 1; fa[u][0] = f; dl[u] = dc++;
    rep (i,B-1) fa[u][i+1] = fa[fa[u][i]][i];
    for (int v: e[u]) if (v!=f) { dfs(v, u); } 
    dr[u] = dc; }
  void up(int &u, int d) {
    rep (i,B) if ((d>>i) & 1) { u = fa[u][i]; } }
  int lca(int u, int v) {
    if (d[u] < d[v]) { std::swap(u,v); } up(u, d[u]-d[v]);
    repb (i,B-1,0) if (fa[u][i] != fa[v][i]) { u=fa[u][i]; v=fa[v][i]; }
    return u==v ? u : fa[u][0]; }
  inline bool include(int u, int v) { return dl[v] >= dl[u] && dl[v] < dr[u]; }
  inline bool onChain(int u, int s, int t) { return include(s, u) && include(u, t); }
  inline int dis(int u, int v) { return d[u] + d[v] - 2*d[lca(u,v)]; }
} T;

bool cmpDep(int u, int v) { return T.d[u] < T.d[v]; }
bool check(int ia, int ib) {
  int u1 = s[ia], v1 = t[ia], l1 = T.lca(u1, v1);
  int u2 = s[ib], v2 = t[ib], l2 = T.lca(u2, v2);
  if (T.d[l1] < T.d[l2]) { std::swap(u1,u2); std::swap(v1,v2); std::swap(l1,l2); }
  if (!T.include(l2, l1)) { return false; }
  int key2 = u2, sp2 = v2; if (T.onChain(l1, l2, v2)) { std::swap(key2, sp2); }
  if (!T.onChain(l1, l2, key2)) { return false; }
  // see(u1,v1,l1); see(u2,v2,l2);
  int st = std::max(T.lca(u1, key2), T.lca(v1, key2), cmpDep);
  int ed = l1; if (l1 == l2) { ed = std::max(T.lca(u1, sp2), T.lca(v1, sp2), cmpDep); }
  // see(st, ed);
  int stt1 = T.dis(u1, st), edt1 = T.dis(u1, ed);
  int stt2 = T.dis(u2, st), edt2 = T.dis(u2, ed); 
  if (stt1 > edt1) { std::swap(stt1, edt1); std::swap(stt2, edt2); }
  if (stt2 > edt2) {
    if (edt2 > edt1 || stt2 < stt1) { return false; }
    else { return true; } }
  else { return stt1 == stt2; }
}

void preInit() { } void init() {
  n = sc.n(); rep (i,n-1) { T.addEdge(sc.n(), sc.n()); } 
  m = sc.n(); rep (i,m) { s[i] = sc.n(); t[i] = sc.n(); }
  T.dfs(1);
} void solve() {
  int ans = 0;
  rep (i,m) rep (j,i) {
    ans += check(i,j); }
  printf("%d\n", ans); 
}
