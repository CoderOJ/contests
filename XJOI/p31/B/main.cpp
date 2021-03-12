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

constexpr int N = 100005;
Tree::TreeLca<N> T;
int k[N], l[N], r[N], n, q;
long long b[N];

void preInit() { } void init() {
  n = sc.n(); q = sc.n();
  repa (i,n) {
    k[i]=sc.n(); b[i]=sc.nl(); l[i]=sc.n(); r[i]=sc.n(); }
  rep (i,n-1) { int u=sc.n(), v=sc.n(); T.addEdge(u,v); }
  T.initLca(1);
} void solve() {
  while (q--) {
    int u=sc.n(), v=sc.n(), x=sc.n();
    int lca = T.lca(u,v);
    long long ans = 0;
    while (u != lca) {
      if (l[u] <= x && x <= r[u]) { checkMax(ans, 1ll*x*k[u] + b[u]); }
      u = T.fa[u][0]; }
    while (v != lca) {
      if (l[v] <= x && x <= r[v]) { checkMax(ans, 1ll*x*k[v] + b[v]); }
      v = T.fa[v][0]; }
    if (l[lca] <= x && x <= r[lca]) { checkMax(ans, 1ll*x*k[lca] + b[lca]); }
    printf("%lld\n", ans); }
}
