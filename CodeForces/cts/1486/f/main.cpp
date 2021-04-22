#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
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

constexpr int N = 300005;
constexpr int B = 20;
Vector<int> e[N];
int n, m;

int fa[N][B], dep[N];
void dfs0(int u, int f) {
  dep[u] = dep[f] + 1; fa[u][0] = f;
  for (int i=0; i+1<B; ++i) fa[u][i+1] = fa[fa[u][i]][i];
  for (int v: e[u]) if (v != f) { dfs0(v,u); } }
int up(int u, int d) {
  if (d < 0) { return 0; }
  for (int i=0; i<B; ++i) if (d & (1 << i)) u = fa[u][i];
  return u; }
int lca(int u, int v) {
  if (dep[u] < dep[v]) { std::swap(u,v); } u = up(u, dep[u] - dep[v]); 
  for (int i=B-1; i>=0; i--) if (fa[u][i] != fa[v][i]) { u=fa[u][i]; v=fa[v][i]; }
  return u == v ? u : fa[u][0]; }

struct QTuple {
  int u, v;
  QTuple(int u, int v, int l) {
    this->u = up(u, dep[u] - dep[l] - 1);
    this->v = up(v, dep[v] - dep[l] - 1);  }
};

std::vector<QTuple> qsonu[N];
int p1cnt[N], b2cnt[N];
long long ans;

void dfs1(int u, int f) {
  for (int v: e[u]) if (v != f) {
    dfs1(v,u); p1cnt[u] += p1cnt[v]; b2cnt[u] += b2cnt[v]; }
  for (const auto& [x,y]: qsonu[u]) { 
    see(u, x, y, p1cnt[u], b2cnt[x], b2cnt[y]);
    ans += p1cnt[u] - b2cnt[x] - b2cnt[y]; } }

template <class KeyType, class ValueType>
ValueType get(const std::map<KeyType, ValueType>& mp, KeyType key) {
  if (!mp.count(key)) { return ValueType(); }
  else { return mp.at(key); } }

std::pair<int,int> make_pair(int a, int b) {
  if (a > b) { std::swap(a,b); }
  return std::make_pair(a, b); }

void preInit() { } void init() {
  n = sc.n();
  for (int i=1; i<n; ++i) {
    int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
  dfs0(1, 0);
  m = sc.n();
  for (int i=0; i<m; ++i) {
    int u=sc.n(), v=sc.n(), l=lca(u,v);
    p1cnt[u]++; p1cnt[v]++; p1cnt[l]-=2; 
    QTuple tu(u, v, l);
    qsonu[l].push_back(tu);
    if (tu.u != 0) { b2cnt[u]++; b2cnt[tu.u]--; }
    if (tu.v != 0) { b2cnt[v]++; b2cnt[tu.v]--; } }
} void solve() {
  dfs1(1,0);
  for (int u=1; u<=n; ++u) {
    int cnt = 0;
    std::map<int, int> cnt1;
    std::map<std::pair<int,int>, int> cnt2;
    for (const auto& [x,y]: qsonu[u]) {
      ans += cnt;
      if (x) ans -= get(cnt1, x);
      if (y) ans -= get(cnt1, y);
      if (x && y) ans += get(cnt2, make_pair(x,y));
      if (x) cnt1[x]++;
      if (y) cnt1[y]++;
      if (x && y) cnt2[make_pair(x,y)]++; 
      cnt++; } }
  printf("%lld\n", ans);
}
