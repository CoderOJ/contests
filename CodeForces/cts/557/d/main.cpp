#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/Vector.h"

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

struct Dsu {
  int p[N], sz[N];
  Dsu() { for (int i: range(N)) { p[i]=i; sz[i]=1; } }
  int get(int u) { return u==p[u] ? u : p[u] = get(p[u]); }
  void merge(int u, int v) { 
    u = get(u); v = get(v);
    p[v] = u; sz[u] += sz[v]; }
  int size(int u) { return sz[get(u)]; }
  int max_size(int n) { return *std::max_element(sz+1, sz+n+1); }
};

Temps::Vector<int> e[N];
int n, m, col[N], cnt[N][2];
Dsu st;

bool dfs(int u) {
  cnt[st.get(u)][col[u]]++;
  for (int v: e[u]) {
    if (col[v] != -1) {
      if (col[v] == col[u]) { return true; } }
    else { 
      col[v] = !col[u];
      if (dfs(v)) { return true; } } }
  return false; }

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  for ([[maybe_unused]] int i: range(m)) {
    int u = sc.n(), v = sc.n(); 
    e[u].push_back(v); e[v].push_back(u); 
    st.merge(u, v); }
} void solve() {
  if (st.max_size(n) == 1) { printf("3 %lld\n", 1ll * n * (n-1) * (n-2) / 6); return; }
  if (st.max_size(n) == 2) { printf("2 %lld\n", 1ll * (n-2) * m); return; }
  std::fill(col+1, col+n+1, -1);
  for (int u: range(1,n+1)) if (col[u] == -1) {
    col[u] = 0; if (dfs(u)) { puts("0 1"); return; } }
  std::set<int> cst; for (int i: range(1,n+1)) { cst.insert(st.get(i)); }
  long long ans = 0;
  for (const int u: cst) {
    ans += 1ll * cnt[u][0] * (cnt[u][0]-1) / 2;
    ans += 1ll * cnt[u][1] * (cnt[u][1]-1) / 2; }
  printf("1 %lld\n", ans);
}
