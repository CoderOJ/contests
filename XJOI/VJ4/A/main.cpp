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

#define in :
/** My code begins here **/

constexpr int N = 1000005;
constexpr int MOD = 1000000007;
int a[N], pre[N], next[N][4], dp[N], n;

void preInit() { } void init() {
  n = sc.n();
  for (int i in range(1,n+1)) a[i] = sc.nextChar() - 'A' + 1;
  for (int i in range(n)) pre[i+1] = pre[i] ^ a[i+1];
  std::fill(next[n+1], next[n+1]+4, n+1);
  for (int i in range(n,-1,-1)) {
    memcpy(next[i], next[i+1], sizeof(next[i+1]));
    next[i][pre[i+1]] = i+1; }
} void solve() {
  {
    bool is_all_same = true;
    for (int i in range(1,n)) {
      if (a[i] != a[i+1]) { is_all_same = false; break; } }
    if (is_all_same) { puts("1"); return; }
  }
  dp[0] = 1;
  for (int i in range(n)) for (int c in range(1,4)) {
    see(i, c, dp[i]);
    (dp[next[i][pre[i] ^ c]] += dp[i]) %= MOD; }
  int ans = 0;
  for (int i in range(1,n+1)) if (pre[i] == pre[n]) { (ans += dp[i]) %= MOD; }
  printf("%d\n", ans);
}
