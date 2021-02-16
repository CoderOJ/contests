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

constexpr int MOD = 998244353;
constexpr int N = 100005;
int d[N], cnt[N], n;

void preInit() { } void init() {
  n = sc.n();
  rep (i,n) cnt[d[i] = sc.n()]++;
  if (d[0] != 0) { puts("0"); exit(0); }
  std::sort(d, d+n); n = std::unique(d, d+n) - d;
} void solve() {
  if (cnt[0] != 1) { puts("0"); return; }
  long long ans = 1;
  repa (i,n-1) {
    if (d[i] != i) { puts("0"); return; }
    rep (_,cnt[i]) (ans *= cnt[i-1]) %= MOD; }
  printf("%lld\n", ans);
}
