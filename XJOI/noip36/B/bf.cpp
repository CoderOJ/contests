#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
#include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

const int N = 200005;
Tree::TreeLca<N> T;
std::set<int> st[N];
int sz[N], n;

void dfs0(int u, int f) {
  sz[u] = 1;
  auto vs = T.getNodes(u);
  for (int v: vs) if (v!=f) { 
    dfs0(v,u); sz[u] += sz[v]; } }

int ans = 0x3f3f3f3f;
void update_ans(int a, int b) { int c = n - a - b; checkMin(ans, std::max( std::abs(a-b), std::max( std::abs(a-c), std::abs(b-c) ) ) ); }

void preInit() { } void init() {
  n = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); T.addEdge(u,v); }
  T.initLca(1); 
} void solve() { 
  dfs0(1,0);
  repa (u,n) repa (v,u-1) {
    int su = sz[u], sv = sz[v], l = T.lca(u,v);
    if (l == u) { su -= sv; }
    if (l == v) { sv -= su; }
    update_ans(su, sv); }
  printf("%d\n", ans);
}
