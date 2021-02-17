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

constexpr int N = 250005;
constexpr int B = 20;

std::vector<int> e[N];
std::set<int> s[N];
int a[N], fa[N][B], dep[N], ans[N], n;

struct FTree {
  int a[N];
  static inline int low(const int u) noexcept { return u&(-u); }
  FTree() { memset(a,0,sizeof(a)); }
  inline void clear() noexcept { memset(a, 0, sizeof(a)); }
  inline void modify(int p, int v) noexcept {
    for (;p<=n;p+=low(p)) checkMax(a[p], v); }
  inline int query(int p) const noexcept {
    int res = 0; for (;p;p-=low(p)) { checkMax(res, a[p]); }
    return res; }
};

int lca(int u, int v) {
  if (dep[u] < dep[v]) { std::swap(u,v); }
  int de = dep[u]-dep[v]; repb (i,B-1,0) if (de & (1<<i)) { u = fa[u][i]; }
  repb (i,B-1,0) if (fa[u][i] != fa[v][i]) { u=fa[u][i]; v=fa[v][i]; }
  return u==v ? u : fa[u][0]; }

void doit(const int a[], const int n) {
  repa (i,n) s[i].clear(); FTree c;
  std::vector<int> id(n); repa (i,n) id[a[i]-1]=i;
  for (const int& u: id) {
    int pre = c.query(u); c.modify(u, pre+1); s[pre+1].insert(u);
    see(u, pre);
    fa[u][0] = pre ? lca(*s[pre].begin(), *--s[pre].lower_bound(u)) : 0;
    dep[u] = dep[fa[u][0]] + 1;
    rep (i,B-1) fa[u][i+1] = fa[fa[u][i]][i]; } }

void preInit() { } void init() {
  n = sc.n(); repa (i,n) a[i] = sc.n();
} void solve() {
  doit(a, n);
  repa (i,n) ans[i] += dep[i] - 1;
  std::reverse(a+1, a+n+1); repa (i,n) a[i] = n-a[i]+1;
  doit(a, n);
  repa (i,n) ans[i] += dep[n-i+1] - 1;
  repa (i,n) printf("%d ", ans[i]);
}
