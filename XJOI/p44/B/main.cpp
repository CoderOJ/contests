#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

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
int a[N], b[N], n;
int dp[N];

void preInit() { } void init() {
  n = sc.n();
  rep (i,n) { a[i] = sc.n(); b[i] = sc.n(); }
} void solve() {
  std::fill(dp, dp+n+1, 0x3f3f3f3f); dp[0] = 0;
  for (int i=1; i<=n; ++i) {
    Vector<int> sa, sb;
    int cur = 0;
    for (int j=i-1; j>=0; j--) {
      while (!sa.empty() && sa.back() > a[j]) { sa.pop_back(); }
      if (sa.empty() || sa.back() < a[j]) { cur++; }
      sa.push_back(a[j]);
      while (!sb.empty() && sb.back() > b[j]) { sb.pop_back(); }
      if (sb.empty() || sb.back() < b[j]) { cur++; }
      sb.push_back(b[j]);
      see(i, j, cur);
      checkMin(dp[i], dp[j] + cur - 1); } }
  logArray(dp, dp+n+1);
  printf("%d\n", dp[n] - 1);
}
