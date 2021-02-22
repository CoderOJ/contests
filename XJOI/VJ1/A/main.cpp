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

constexpr int N = 200005;
std::vector<int> e[N];
int n, m, k;

struct Dsu {
  int p[N];
  Dsu() { rep (i,N) p[i] = i; }
  int get(int u) { return u == p[u] ? u : p[u] = get(p[u]); }
} st;

std::vector<int> ord;
void dfs(int u, int f) {
  ord.push_back(u);
  for (int v: e[u]) if (v!=f) {
    dfs(v,u); ord.push_back(u); } }

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); k = sc.n();
  rep (i,m) { int u=sc.n(), v=sc.n();
    int pu = st.get(u), pv = st.get(v);
    if (pu != pv) {
      st.p[pu] = pv;
      e[u].push_back(v); e[v].push_back(u); } }
} void solve() {
  dfs(1, 0);
  int lim = (2*n + k-1) / k;
  rep (i,k) {
    int st = lim * i, ed = std::min(st+lim, (int)ord.size());
    if (ed <= st) { st = ed - 1; }
    printf("%d", ed - st);
    for (int j=st; j<ed; ++j) { printf(" %d", ord[j]); }
    puts(""); }
}
