#pragma GCC optimize(2,3,"Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
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

constexpr int N = 100005;
long long a[N], n, dp[N];

inline void chmax(long long &a, long long b) { (a < b) && (a = b); }

void preInit() { } void init() {
  n = sc.n(); 
  for (int i: range(n)) { a[i] = sc.nextInt(); }
} void solve() {
  std::fill(dp, dp+n+1, std::numeric_limits<long long>::min() / 2);
  dp[0] = 0;
  for (int i=0;i<n;++i) {
    for (int j=i+1;j>0;--j) {
      chmax(dp[j], dp[j-1] + a[i]*j); } }
  printf("%lld\n", *std::max_element(dp, dp+n+1));
}
