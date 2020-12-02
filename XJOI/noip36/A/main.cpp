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

const int N = 100005;
struct Edge { int u,v,w; } e[N];
int val[N], p[N], n;

int get(int u) { return u==p[u] ? u : p[u] = get(p[u]); }

void preInit() { } void init() {
  n = sc.n(); repa (i,n) val[i] = sc.n();
  rep (i,n-1) { e[i].u=sc.n(); e[i].v=sc.n(); e[i].w = std::max(val[e[i].u], val[e[i].v]); }
  repa (i,n) p[i] = i;
} void solve() {  
  std::sort(e, e+n-1, [](Edge a, Edge b) { return a.w < b.w; });
  long long ans = 0;
  rep (i,n-1) { int u=e[i].u, v=e[i].v;
    int pu=get(u), pv=get(v);
    ans += val[pu] + val[pv];
    p[pv] = pu; checkMax(val[pu], val[pv]); }
  printf("%lld\n", ans);
}
