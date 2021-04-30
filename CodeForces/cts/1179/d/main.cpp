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

constexpr int N = 500005;
Vector<int> e[N];
int n;

int size[N];
void get_size(int u, int f) { size[u] = 1; for (int v: e[u]) if (v != f) get_size(v, u), size[u] += size[v]; }
std::pair<long long, int> dfs(int u, int f) {
  std::pair<long long, int> res(1ll * size[u] * (size[u]-1), u);
  for (int v: e[u]) if (v != f) {
    auto v_res = dfs(v, u); 
    v_res.first += 1ll * (size[u] - size[v]) * (size[u] - size[v] - 1); 
    checkMin(res, v_res); }
  return res; }

void preInit() { } void init() {
  n = sc.n();
  for (int i=1; i<n; ++i) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} void solve() {
  long long min_del = std::numeric_limits<decltype(min_del)>::max();
  std::mt19937 rd(20050610); 
  int pos = rd() % n + 1;
  for (int i=0; i<2; ++i) {
    get_size(pos, 0); auto res = dfs(pos, 0);
    checkMin(min_del, res.first); pos = res.second; }
  printf("%lld\n", 1ll * n * (n-1) -  min_del / 2); }
