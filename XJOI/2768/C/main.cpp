#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 100005;
constexpr int B = 20;
struct edge_t { int v; long long w; };
std::vector<edge_t> e[N];
int n, m, g_l, g_r;

struct LCT {
  struct Node {
    Node *f=nullptr, *s[2]={nullptr, nullptr};
    long long val=0, sum=0, cnt=1, add=0;
    bool is_root() { return f == nullptr || (f->s[0] != this && f->s[1] != this); }
    bool get_son() { return f->s[1] == this; }
    void push_up() { 
      sum = val, cnt = 1; 
      if (s[0]) { sum += s[0]->sum; cnt += s[0]->cnt; }
      if (s[1]) { sum += s[1]->sum; cnt += s[1]->cnt; } }
    void push_add(long long delta) {
      add += delta; val += delta; sum += cnt * delta; }
    void push_down() {
      if (add) { if (s[0]) s[0]->push_add(add); if (s[1]) s[1]->push_add(add); add = 0; } }
    void push() { if (!is_root()) { f->push(); } push_down(); }
    void rotate() { 
      Node *const uu=this, *const ff=f, *const aa=ff->f; const bool ss = get_son();
      if (!ff->is_root()) aa->s[ff->get_son()] = uu;
      ff->f = uu; ff->s[ss] = uu->s[!ss];
      uu->f = aa; uu->s[!ss] = ff;
      if (ff->s[ss]) ff->s[ss]->f = ff; 
      ff->push_up(); uu->push_up(); }
    void splay() { push();
      while (!is_root()) {
        if (f->is_root()) { rotate(); return; }
        (get_son() == f->get_son() ? f : this)->rotate(); rotate(); } }
    void access() {
      Node *uu=this, *ss=nullptr;
      while (uu) {
        uu->splay(); uu->s[1] = ss; uu->push_up();
        ss = uu; uu = uu->f; } }
  } p[N];
} T;

int d[N], fa[N][B], dfn[N], dfn_top=0;
void dfs(int u, int f) {
  d[u] = d[f] + 1; fa[u][0] = f; dfn[u] = dfn_top++;
  for (int i=0; i+1<B; i++) fa[u][i+1] = fa[fa[u][i]][i];
  for (const auto& v: e[u]) if (v.v != f) {
    T.p[v.v].f = &T.p[u]; T.p[v.v].push_add(v.w); dfs(v.v, u); } }
int lca(int u, int v) {
  if (d[u] < d[v]) std::swap(u, v);
  int delta = d[u] - d[v]; for (int i=0; i<B; ++i) if (delta & (1 << i)) u = fa[u][i];
  for (int i=B-1; i>=0; i--) if (fa[u][i] != fa[v][i]) { u = fa[u][i]; v = fa[v][i]; }
  return u == v ? u : fa[u][0]; }

bool act_u[N];
struct edge2_t { int v,de; long long dw; };
std::vector<edge2_t> e2[N];
std::vector<int> used_u;
void add_edge2(int u, int v) {
  long long dis = 0;
  T.p[u].access(); T.p[u].splay(); dis -= T.p[u].sum; 
  T.p[v].access(); T.p[v].splay(); dis += T.p[v].sum; 
  dis = std::abs(dis);
  int we = std::abs(d[u] - d[v]);
  e2[u].push_back({v, we, dis}); e2[v].push_back({u, we, dis}); }

void build_vtree(std::vector<int> &&us) {
  used_u = us;
  std::sort(us.begin(), us.end(), [](int a, int b) { return dfn[a] < dfn[b]; });
  static int stack[N]; int *top = stack;
  if (us[0] != 1) { *top++ = 1; used_u.push_back(1); }
  for (int u: us) {
    act_u[u] = true;
    while (top - stack >= 2) {
      int l = lca(top[-1], u);
      if (l == top[-1]) { break; }
      else if (d[l] <= d[top[-2]]) { add_edge2(top[-2], top[-1]); top--; }
      else { used_u.push_back(l); add_edge2(l, top[-1]); top[-1] = l; break; } }
    *top++ = u; }
  while (top - stack >= 2) { add_edge2(top[-2], top[-1]); top--; } }

template <class A, class B> 
inline std::pair<A, B> operator+ (const std::pair<A,B> lhs, const std::pair<A,B> rhs) {
  return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second); }
template <class A, class B> 
inline std::pair<A, B> operator- (const std::pair<A,B> lhs, const std::pair<A,B> rhs) {
  return std::make_pair(lhs.first - rhs.first, lhs.second - rhs.second); }
struct FTree {
  static inline int low(int u) { return u & (-u); }
  std::pair<int, long long> a[N + 5];
  void modify(int p, std::pair<int, long long> delta) { p += 5;
    while (p < N + 5) { a[p] = a[p] + delta; p += low(p); } }
  void reset(int p) { p += 5;
    if (a[p].first == 0 && a[p].second == 0) { return; }
    while (p < N + 5) { a[p] = {0, 0}; p += low(p); } }
  std::pair<int, long long> query(int p) { p += 5;
    std::pair<int, long long> ans = {0,0};
    while (p) { ans = ans + a[p]; p -= low(p); } 
    return ans; }
  std::pair<int, long long> query(int l, int r) {
    if (r < 0) { return {0,0}; }
    if (l < 0) { l = 0; }
    return query(r) - query(l - 1); }
} pw;

bool vis[N];
int size[N], best_val, best_u, tot_size;
void get_size(int u, int f) {
  size[u] = 1;
  for (const auto& v: e2[u]) if (!vis[v.v] && v.v != f) { 
    get_size(v.v, u); size[u] += size[v.v]; } }
void get_root(int u, int f) {
  int val = tot_size - size[u];
  for (const auto& v: e2[u]) if (!vis[v.v] && v.v != f) { 
    checkMax(val, size[v.v]); get_root(v.v, u); }
  if (checkMin(best_val, val)) { best_u = u; } }

struct mod_record_t { int p; long long val; };
std::vector<mod_record_t> current;
std::vector<int> legacy;

long long ans = 0;
void dfs_mod(int u, int f, int de, long long dw) {
  if (act_u[u]) { current.push_back({de, dw}); }
  for (const auto& v: e2[u]) if (!vis[v.v] && v.v != f) {
    dfs_mod(v.v, u, de + v.de, dw + v.dw); } }
void dac(int u) {
  get_size(u, 0);
  if (size[u] == 1) { return; }
  tot_size = size[u]; best_val = n + 1; get_root(u, 0);
  u = best_u; vis[u] = true;
  legacy.clear();
  if (act_u[u]) { legacy.push_back(0); pw.modify(0,{1,0}); }
  for (const auto v: e2[u]) if (!vis[v.v]) {
    current.clear();
    dfs_mod(v.v, u, v.de, v.dw);
    for (const auto rv: current) {
      auto pw_res = pw.query(g_l - rv.p, g_r - rv.p);
      ans += pw_res.second + pw_res.first * rv.val; }
    for (const auto rv: current) {
      legacy.push_back(rv.p); pw.modify(rv.p, {1,rv.val}); } }
  for (const auto rv: legacy) { pw.reset(rv); }
  for (const auto v: e2[u]) if (!vis[v.v]) dac(v.v); }
    
void preInit() {  } void init() {
  n = sc.n(); m = sc.n();
  for (int i=1; i<n; ++i) {
    int u=sc.n(), v=sc.n(), w=sc.n(); e[u].push_back({v,w}); e[v].push_back({u,w}); } } 

void solve() {
  dfs(1, 0);
  for (int cs=0; cs<m; cs++) {
    int opt = sc.n();
    if (opt == 1) {
      int u=sc.n(), v=sc.n(); long long w=sc.nl();
      int l = lca(u, v);
      T.p[u].access(); T.p[u].splay(); T.p[u].push_add(w);
      T.p[v].access(); T.p[v].splay(); T.p[v].push_add(w);
      T.p[l].access(); T.p[l].splay(); T.p[l].push_add(-2 * w); }
    else if (opt == 2) {
      g_l=sc.n(); g_r=sc.n(); int k=sc.n(); std::vector<int> us;
      for (int i=0; i<k; ++i) us.push_back(sc.n());
      build_vtree(std::move(us)); 
      ans = 0; dac(1);
      printf("%lld\n", ans);
      for (int u: used_u) { 
        e2[u].clear(); act_u[u] = false; 
        vis[u] = false; }
      used_u.clear(); } } }
