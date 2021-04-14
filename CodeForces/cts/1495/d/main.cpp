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

constexpr int MOD = 998244353;
constexpr int N = 405;
int ans[N][N], e[N][N], c[N], n, m;
Temps::Vector<std::pair<int,int>> es;

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); es.resize(m);
  memset(e, 0x3f, sizeof(e)); for (int u: range(n)) e[u][u] = 0;
  for (int i: range(m)) { 
    int u=sc.n()-1, v=sc.n()-1; es[i] = {u,v}; e[v][u] = e[u][v] = 1; }
} void solve() {
  for (int r: range(n)) for (int u: range(n)) for (int v: range(n)) checkMin(e[u][v], e[u][r] + e[r][v]);
  for (int s: range(n)) for (int t: range(s + 1)) {
    std::fill(c, c+n, 0); int onpath_cnt = 0;
    for (int i: range(n)) if (e[s][t] == e[s][i] + e[i][t]) { c[i]=1; onpath_cnt++; }
    for (const auto& [u,v]: es) {
      if ((e[s][u] == e[s][v] + 1) && (e[t][u] == e[t][v] + 1)) { c[u]++; }
      if ((e[s][v] == e[s][u] + 1) && (e[t][v] == e[t][u] + 1)) { c[v]++; } }
    long long ans = onpath_cnt <= e[s][t] + 1; 
    for (int i: range(n)) ans = 1ll * ans * c[i] % MOD; 
    ::ans[s][t] = ::ans[t][s] = ans; }
  for (int u: range(n)) for (int v: range(n)) printf("%d%c", ans[u][v], " \n"[v==n-1]);
}
