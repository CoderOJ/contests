#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
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

constexpr int N = 1005;
int dp[N][2];
char s[N];

void preInit() { } void init() {
} void solve() {
  int T = sc.n();
  for (int _case: range(1, T+1)) {
    int x=sc.nextInt(), y=sc.nextInt(); sc.next(s);
    int n = std::strlen(s);
    if (s[0] == 'C') { dp[0][0] = 0; dp[0][1] = 0x3f3f3f3f; }
    else if (s[0] == 'J') { dp[0][1] = 0; dp[0][0] = 0x3f3f3f3f; }
    else { dp[0][0] = dp[0][1] = 0; }
    for (int i: range(1,n)) {
      if (s[i] == 'C') { dp[i][0] = std::min(dp[i-1][0], dp[i-1][1] + y); dp[i][1] = 0x3f3f3f3f; }
      else if (s[i] == 'J') { dp[i][1] = std::min(dp[i-1][0] + x, dp[i-1][1]); dp[i][0] = 0x3f3f3f3f; }
      else { dp[i][0] = std::min(dp[i-1][0], dp[i-1][1] + y); dp[i][1] = std::min(dp[i-1][0] + x, dp[i-1][1]); } }
    printf("Case #%d: %d\n", _case, std::min(dp[n-1][0], dp[n-1][1])); }
}
