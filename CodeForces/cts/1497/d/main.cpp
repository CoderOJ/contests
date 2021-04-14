#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 5005;
int tag[N], s[N], n;
long long dp[N];

void preInit() { } void init() {
  n = sc.n();
  for (int i: range(n)) { tag[i] = sc.n(); }
  for (int i: range(n)) { s[i] = sc.n(); }
  std::fill(dp, dp+n, 0);
} void solve() {
  for (int u=1;u<n;++u) for (int v=u-1;v>=0;v--) if (tag[u] != tag[v]) {
    int ds = std::abs(s[u] - s[v]);
    long long du = dp[v] + ds, dv = dp[u] + ds;
    checkMax(dp[u], du); checkMax(dp[v], dv); }
  std::cout << *std::max_element(dp, dp+n) << std::endl;
}
