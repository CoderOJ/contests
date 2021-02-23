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

#define long long long
constexpr int N = 300005;
int w[N], n;

struct Tree {
  std::vector<int> e[N];
  void addEdge(int u, int v) {
    e[u].push_back(v); e[v].push_back(u); }
};

inline bool checkSlope(const std::pair<long,long>& a, decltype(a) b, decltype(a) c) {
  long dax = b.first - a.first, day = b.second - a.second;
  long dbx = c.first - b.first, dby = c.second - b.second;
  return static_cast<__int128_t>(dax) * dby < static_cast<__int128_t>(day) * dbx; }
inline long max_calc(const std::pair<long,long>& a, decltype(a) b) {
  return a.second + a.first * b.first + b.second; }
long get_max(std::vector<std::pair<long,long>> points, std::vector<std::pair<long,long>> querys) {
  if (points.size() == 0 || querys.size() == 0) { return 0; }
  std::sort(points.begin(), points.end(), [](const std::pair<long,long>& a, decltype(a) b) {
    return a.first < b.first; });
  std::sort(querys.begin(), querys.end(), [](const std::pair<long,long>& a, decltype(a) b) {
    return a.first < b.first; });
  logArray(points.begin(), points.end());
  logArray(querys.begin(), querys.end());
  std::vector<std::pair<long,long>> st;
  for (const auto& p: points) {
    while (st.size() >= 2) {
      const auto& p0 = st[st.size()-2], p1=st[st.size()-1];
      if (!checkSlope(p0, p1, p)) { st.pop_back(); }
      else { break; } }
    st.push_back(p); }
  long res = 0; std::size_t best_id = 0;
  for (const auto& p: querys) {
    while (best_id+1 < st.size() && max_calc(st[best_id], p) <= max_calc(st[best_id+1], p)) { best_id++; }
    checkMax(res, max_calc(st[best_id], p)); }
  return res; }

struct TreePD : public Tree {
  bool vis[N];
  TreePD() { memset(vis,true,sizeof(vis)); }
  int size[N], totSize, rootC, root;
  void getSize(int u, int f) {
    size[u] = 1;
    for (int v: e[u]) if (vis[v] && v != f) {
      getSize(v,u); size[u] += size[v]; } }
  void getRoot(int u, int f) {
    int cost = totSize - size[u];
    for (int v: e[u]) if (vis[v] && v != f) {
      getRoot(v,u); checkMax(cost, size[v]); }
    if (checkMin(rootC, cost)) { root = u; } }
  void get(int u) {
    getSize(u,u); totSize = size[u];
    rootC = std::numeric_limits<int>::max(); getRoot(u,u); }

  void dfsDown(int u, int f, std::vector<std::pair<long,long>>& g, long pre_cnt=0, long pre_sum=0, long pre_tot=0) {
    if (u <= n) { pre_cnt++; pre_sum += w[u]; pre_tot += pre_cnt * w[u]; g.push_back(std::make_pair(pre_sum, pre_tot)); }
    for (int v: e[u]) if (vis[v] && v != f) {
      dfsDown(v, u, g, pre_cnt, pre_sum,  pre_tot); } }
  void dfsUp(int u, int f, std::vector<std::pair<long,long>>& g, long pre_cnt=0, long pre_sum=0, long pre_tot=0) {
    if (u <= n) { pre_cnt++; pre_sum += w[u]; pre_tot += pre_sum; g.push_back(std::make_pair(pre_cnt, pre_tot)); }
    for (int v: e[u]) if (vis[v] && v != f) { 
      dfsUp(v, u, g, pre_cnt, pre_sum , pre_tot); } }
  long dfs(int u) {
    get(u); u = root; vis[root] = false;
    see(u);
    std::vector< std::vector<std::pair<long,long>> > up, down;
    for (int v: e[u]) if (vis[v]) {
      std::vector<std::pair<long,long>> a, b;
      dfsDown(v,u,a, 1,w[u],w[u]); dfsUp(v,u,b); 
      down.emplace_back(std::move(a)); up.emplace_back(std::move(b)); }
    int top = up.size();
    long ans = 0;
    for (int B=1;B<top;B<<=1) {
      std::vector<std::pair<long,long>> a,b;
      for (int i=0;i<top;++i) {
        if (i & B) { for (const auto& p: down[i]) { a.push_back(p); } }
        else { for (const auto& p: up[i]) { b.push_back(p); } } }
      checkMax(ans, get_max(a,b));
      a.clear(); b.clear();
      for (int i=0;i<top;++i) {
        if (!(i & B)) { for (const auto& p: down[i]) { a.push_back(p); } }
        else { for (const auto& p: up[i]) { b.push_back(p); } } }
      checkMax(ans, get_max(a,b)); }
    for (int v: e[u]) if (vis[v]) { checkMax(ans, dfs(v)); }
    return ans; }
} Tsolve;

void preInit() { } void init() {
  n = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); Tsolve.addEdge(u,v); }
  repa (i,n) w[i] = sc.n();
} void solve() {
  if (n == 2) { printf("%d\n", std::max(w[1]+w[2]*2, w[2]+w[1]*2)); return; }
  printf("%lld\n", Tsolve.dfs(1));
}
