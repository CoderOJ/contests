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

template <class _Type>
struct FTree {
  static constexpr int OFFSET = 2;
  typedef _Type value_type;
  value_type *a = nullptr;
  int len = 0;

  void resize(int size) noexcept {
    delete[] a; a = new value_type[len = size + OFFSET](); }

  static inline int low(int a) { 
    return a & (-a); }
  void modify(int pos, const value_type& val) {
    pos += OFFSET; while (pos < len) { a[pos] += val; pos += low(pos); } }
  value_type query(int pos) const {
    if (pos < 0) { return 0; }
    pos += OFFSET; value_type res = value_type();
    if (pos >= len) { pos = len - 1; }
    while (pos) { res += a[pos]; pos -= low(pos); }
    return res; }
  ~FTree() { delete[] a; }
};

constexpr int N = 100005;
constexpr int B = 20;
std::vector<int> e[N];
int n, m;

int pd_dep[N], vis[N], size[N], height[N];
int g_dep[B][N], g_br[B][N], g_brs[B][N];
int *dep, *br, *brs;
FTree<int> g_ft[B][N], *ft;

void getSize(int u, int f) {
  size[u] = 1; 
  for (int v: e[u]) if (v != f && !vis[v]) {
    getSize(v, u); size[u] += size[v]; } }
int g_size, g_root, g_best;
void getRoot(int u, int f) {
  int pos = g_size - size[u];
  for (int v: e[u]) if (v != f && !vis[v]) {
    getRoot(v, u); checkMax(pos, size[v]); }
  if (checkMin(g_best, pos)) { g_root = u; } }
void get(int u, int pd_f) {
  getSize(u, 0);  g_size = size[u]; g_best = std::numeric_limits<decltype(g_best)>::max();
  getRoot(u, 0); pd_dep[g_root] = pd_dep[pd_f] + 1; vis[g_root] = 1; 
  int d = pd_dep[g_root];
  dep = g_dep[d]; br = g_br[d]; brs = g_brs[d]; }

void calc(int u, int f, int r, int rs) {
  dep[u] = dep[f] + 1; height[u] = 0; br[u] = r; brs[u] = rs;
  for (int v: e[u]) if (v != f && !vis[v]) {
    calc(v, u, r, rs); checkMax(height[u], height[v] + 1); } }
void dfs(int u, int pd_f) {
  get(u, pd_f); u = g_root; ft = g_ft[pd_dep[u]];
  dep[u] = 0; height[u] = 0; br[u] = u;
  for (int v: e[u]) if (!vis[v]) { 
    calc(v, u, u, v); checkMax(height[u], height[v] + 1); 
    ft[v].resize(height[v] + 1); }
  ft[u].resize(height[u] + 1); 
  for (int v: e[u]) if (!vis[v]) { dfs(v, u); } }

int value[N];
void modify(int u, int uval) {
  int del = uval - value[u]; value[u] = uval;
  rep (i,B) {
    int d = g_dep[i][u];
    if (g_br[i][u] != -1) { g_ft[i][ g_br[i][u] ].modify(d, del); }
    if (g_brs[i][u] != -1) { g_ft[i][ g_brs[i][u] ].modify(d - 1, del); } } }
int query(int u, int qd) {
  int res = 0;
  rep (i,B) {
    int d = g_dep[i][u];
    if (g_br[i][u] != -1) { res += g_ft[i][ g_br[i][u] ].query(qd - d); }
    if (g_brs[i][u] != -1) { res -= g_ft[i][ g_brs[i][u] ].query(qd - d - 1); } }
  return res; }

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  repa (i,n) value[i] = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
  memset(g_dep, -1, sizeof(g_dep)); memset(g_br, -1, sizeof(g_br)); memset(g_brs, -1, sizeof(g_brs));
  pd_dep[0] = -1; dfs(1, 0);
  repa (i,n) { int del = value[i]; value[i] = 0; modify(i, del); }
} void solve() {
  // repa (i,n) rep (j,3) { see(i, j); see(g_dep[j][i], g_br[j][i], g_brs[j][i]); }
  int last_ans = 0;
  rep (i,m) {
    int opt=sc.n(), u=sc.n() ^ last_ans, d=sc.n() ^ last_ans;
    if (opt == 1) { modify(u, d); }
    else { printf("%d\n", last_ans = query(u, d)); } }
}
