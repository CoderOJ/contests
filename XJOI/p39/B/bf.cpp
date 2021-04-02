#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/util.h"

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

constexpr int N = 500005;
int n, p, q, r;
int a[N], b[N], c[N];

void preInit() { } void init() {
  n = sc.n(); p = sc.n(); q = sc.n(); r = sc.n();
  for (int i=0; i<n; ++i) { a[i]=sc.n(); b[i]=sc.n(); c[i]=sc.n(); }
} void solve() {
  int ans = 0;
  repa (x, p) repa (y, q) repa (z, r) {
    int cnt = 0;
    rep (i,n) cnt += ((x > a[i]) + (y > b[i]) + (z > c[i])) >= 2;
    ans += cnt == n; }
  printf("%d\n", ans);
}
