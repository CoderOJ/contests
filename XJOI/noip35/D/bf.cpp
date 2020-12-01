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

#define long long long
const int N = 100005;
Tree::TreeLca<N> T;
int col[N], val[N];
int n,q;
long ans = 0;

auto add = [](int u) -> long {
  long res = 0;
  repa (i,n) {
    if (col[i] != col[u]) continue;
    int l = T.lca(u,i);
    if (l != u && l != i) res += val[u] ^ val[i]; } 
  return res;
};

void preInit() { } void init() {
  n = sc.n();
  repa (i,n) col[i] = sc.n();
  repa (i,n) val[i] = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(); T.addEdge(u,v); }
  T.initLca(1);
  repa (i,n) ans += add(i);
  ans /= 2;
} void solve() { 
  printf("%lld\n", ans);
  q = sc.n();
  while (q--) {
    int opt=sc.n(), u=sc.n(), w=sc.n();
    if (opt == 1) { ans -= add(u); val[u]=w; ans += add(u); }
    else { ans -= add(u); col[u]=w; ans += add(u); } 
    printf("%lld\n", ans); }
}
