#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
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

constexpr int N = 100005;

int w[N];

Temps::Vector<int> e[N];
int n;

void dfs0(int u, int f) {
  w[u] = 0;
  for (int v: e[u]) if (v != f) {
    dfs0(v,u); checkMax(w[u], w[v]+1); } }

void dfs1(int u, int f, int pre=std::numeric_limits<int>::min()) {
  checkMax(w[u], pre);
  Temps::Vector<int> sl(1,0), sr(1,0);
  sl.reserve(e[u].size() + 1); sr.reserve(e[u].size() + 1);

  for (int v: e[u]) if (v != f) {
    sl.push_back(std::max(sl.back(), w[v] + 1)); }
  sl.pop_back();

  std::reverse(e[u].begin(), e[u].end());
  for (int v: e[u]) if (v != f) {
    sr.push_back(std::max(sr.back(), w[v] + 1)); }
  std::reverse(e[u].begin(), e[u].end());
  sr.pop_back(); std::reverse(sr.begin(), sr.end()); 

  auto il = sl.begin(), ir = sr.begin();
  for (int v: e[u]) if (v != f) {
    dfs1(v,u, std::max(pre, std::max(*il++, *ir++)) + 1); } }

void preInit() { } void init() {
  n = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} void solve() {
  dfs0(1,0); dfs1(1,0);
  int d = 0; repa (i,n) checkMax(d, w[i]);
  int d_cnt = 0; repa (i,n) d_cnt += (w[i] == d);
  if (d_cnt == 2 || (d_cnt == 3 && n % 2 == 0)) { printf("%d\n", d-1); }
  else { printf("%d\n", d); }
}
