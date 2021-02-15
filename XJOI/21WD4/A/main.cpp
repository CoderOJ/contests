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
int a[N], n;

void preInit() { } void init() {
  n = sc.n();
  rep (i,n) a[i] = sc.n();
  std::sort(a, a+n);
} void solve() {
//  if (n == 2) { printf("%d\n", a[1]-a[0]); return; }
  if (n % 2 == 0) {
    long long ans = 0;
    rep (i,n) {
      if (i < n / 2) { ans -= a[i] * (i==n/2-1 ? 1 : 2); }
      else { ans += a[i] * (i==n/2 ? 1 : 2); } }
    printf("%lld\n", ans); }
  else {
    long long ans1 = 0;
    rep (i,n) {
      if (i < n / 2) { ans1 -= a[i] * 2; }
      else { ans1 += a[i] * (i<=n/2+1 ? 1 : 2); } }
    long long ans2 = 0;
    rep (i,n) {
      if (i <= n / 2) { ans2 -= a[i] * (i>=n/2-1 ? 1 : 2); }
      else { ans2 += a[i] * 2; } }
    printf("%lld\n", std::max(ans1, ans2)); }
}
