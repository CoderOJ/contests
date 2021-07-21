#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
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
struct opt_t { int type, u, v, x; } op[N];
std::vector<int> e[N];
int n, m;

int d[N], fa[N][B];
void dfs(int u, int f) {
  d[u] = d[f] + 1; fa[u][0] = f;
  for (int i=0; i+1<B; i++) fa[u][i+1] = fa[fa[u][i]][i];
  for (int v: e[u]) if (v != f) dfs(v, u); }
int lca(int u, int v) {
  if (d[u] < d[v]) return lca(v, u);
  int delta = d[u] - d[v]; for (int i=0; i<B; i++) if (delta & (1 << i)) u=fa[u][i];
  for (int i=B-1; i>=0; i--) if (fa[u][i] != fa[v][i]) { u = fa[u][i], v = fa[v][i]; }
  return u==v ? u : fa[u][0]; }

void preInit() {  } 
void init() 
{
  n = sc.n(); m = sc.n();
  for (int i=1; i<n; i++) {
    int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
  for (int i=0; i<m; i++) { 
    op[i].type = sc.n();
    if (op[i].type == 1) { op[i].u=sc.n(), op[i].v=sc.n(), op[i].x=sc.n(); }
    else { op[i].u=sc.n(), op[i].x=sc.n(); } }
} 

namespace brute 
{
bool val[N];
int root = 1;

bool valid() { return 1ll * n * m <= 1000000; }
bool dfs_path(int u, int f, int to, std::function<void(int)> func) {
  bool res = u == to;
  for (int v: e[u]) if (v != f) { res |= dfs_path(v, u, to, func); }
  if (res) { func(u); }
  return res; }
void dfs_subtree(int u, int f, int to, bool in, std::function<void(int)> func) {
  in |= u == to; if (in) { func(u); }
  for (int v: e[u]) if (v != f) { dfs_subtree(v, u, to, in, func); } }
int dep[N], ans = 0;
void dfs_ans(int u, int f) {
  dep[u] = 0;
  for (int v: e[u]) if (v != f) { dfs_ans(v, u); checkMax(dep[u], dep[v] + 1); }
  if (val[u]) { ans ^= dep[u]; } }
void main() {
  memset(val, true, sizeof(val));
  for (int i=0; i<m; i++) {
    if (op[i].type == 1) {
      dfs_path(op[i].u, 0, op[i].v, [](int u) { val[u] = !val[u]; });
      ans = 0; dfs_ans(root = op[i].x, 0); printf("%d\n", ans); }
    else {
      dfs_subtree(root, 0, op[i].u, false, [](int u) { val[u] = !val[u]; });
      ans = 0; dfs_ans(root = op[i].x, 0); printf("%d\n", ans); } } }
}

namespace x1 
{
int dep[N], sub[N], up[N];
bool valid() {
  return std::count_if(op, op+m, [](opt_t x) { return x.x != 1; }) == 0; }
void dfs0(int u, int f) { dep[u] = 0;
  for (int v: e[u]) if (v != f) { dfs0(v, u); checkMax(dep[u], dep[v] + 1); } }
void dfs1(int u, int f) { sub[u] = dep[u]; up[u] = up[f] ^ dep[u]; 
  for (int v: e[u]) if (v != f) { dfs1(v, u); sub[u] ^= sub[v]; } }
void main() {
  ::dfs(1, 0); dfs0(1, 0); dfs1(1, 0);
  int ans = sub[1];
  for (int i=0; i<m; i++) {
    if (op[i].type == 1) {
      int l = ::lca(op[i].u, op[i].v);
      ans ^= up[op[i].u] ^ up[op[i].v] ^ dep[l]; }
    else { ans ^= sub[op[i].u]; }
    printf("%d\n", ans); } }
}

void solve() 
{
  if (brute::valid()) { brute::main(); return; }
  if (x1::valid()) { x1::main(); return; }
}
