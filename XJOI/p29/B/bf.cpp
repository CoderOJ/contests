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
#define int long long

/** My code begins here **/

constexpr int N = 100;
int a[N], pre[N], n;

void preInit() { } void init() {
  n = sc.n(); rep (i,n) a[i] = sc.n();
} void solve() {
  int ans = std::numeric_limits<int>::max();
  rep (i,(1<<n)) {
    rep (j,n) { pre[j+1] = pre[j] + ((i & (1<<j)) ? -a[j] : a[j]); }
    int max_pre = 0;
    repi (i,2,n) {
      checkMax(max_pre, pre[i-2]);
      if (pre[i] - max_pre <= 0) { goto fail; } }
    checkMin(ans, pre[n]);
fail:; }
  printf("%lld\n", ans);
}
