#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 1000005;
constexpr int MOD = 998244353;
int n, k, x;

int tot;

int get_longer_cnt(int l) {
  static int dp[N], last=0;
  if (last != 0) {
    dp[last] += k;
    for (int i=last; i<l; ++i) dp[i + 1] = 1ll * dp[i] * k % MOD;
    dp[l] -= k;
    last = l; }
  else {
    dp[0] = 1;
    for (int i=0; i<l; ++i) dp[i + 1] = 1ll * dp[i] * k % MOD;
    dp[l] -= k; }

  if (l <= 16) {
    for (int i=l; i<n; ++i) 
      dp[i + 1] = (1ll * dp[i] * k - 1ll * dp[i - l + 1] * (k-1)) % MOD; }
  else 
  {
    int i;
    for (i=l; i<n; i += 4)
    {
      dp[i + 1] = (1ll * dp[i + 0] * k - 1ll * dp[i - l + 1] * (k-1)) % MOD; 
      dp[i + 2] = (1ll * dp[i + 1] * k - 1ll * dp[i - l + 2] * (k-1)) % MOD; 
      dp[i + 3] = (1ll * dp[i + 2] * k - 1ll * dp[i - l + 3] * (k-1)) % MOD; 
      dp[i + 4] = (1ll * dp[i + 3] * k - 1ll * dp[i - l + 4] * (k-1)) % MOD; 
    }
    for (; i<n; ++i) 
      dp[i + 1] = (1ll * dp[i] * k - 1ll * dp[i - l + 1] * (k-1)) % MOD;
  }

  return (tot - dp[n]) % MOD; }

int get_longer_cnt_k2(int l) {
  constexpr int k = 2;
  static long long dp[N];
  static int last=0;
  if (last != 0) {
    dp[last] += k;
    for (int i=last; i<l; ++i) dp[i + 1] = 1ll * dp[i] * k % MOD;
    dp[l] -= k;
    last = l; }
  else {
    dp[0] = 1;
    for (int i=0; i<l; ++i) dp[i + 1] = 1ll * dp[i] * k % MOD;
    dp[l] -= k; }

  if (l <= 16) {
    for (int i=l; i<n; ++i) 
      dp[i + 1] = (1ll * dp[i] * k - 1ll * dp[i - l + 1] * (k-1)) % MOD; }
  else 
  {
    if (dp[l] < 0) { dp[l] += MOD; }
    int i;
    for (i=l; i<n; i += 8)
    {
      dp[i + 1] = (dp[i + 0] * k - dp[i - l + 1]);
      dp[i + 2] = (dp[i + 1] * k - dp[i - l + 2]); 
      dp[i + 3] = (dp[i + 2] * k - dp[i - l + 3]); 
      dp[i + 4] = (dp[i + 3] * k - dp[i - l + 4]); 
      dp[i + 1] %= MOD; 
      dp[i + 2] %= MOD;
      dp[i + 3] %= MOD;
      dp[i + 4] %= MOD;
    }
    for (; i<n; ++i) 
      dp[i + 1] = (1ll * dp[i] * k - 1ll * dp[i - l + 1] * (k-1)) % MOD;
  }

  return (tot - dp[n]) % MOD; }


void preInit() { } void init() {
  n = sc.n(); k = sc.n(); x = sc.n();
  tot=1; for (int i=0; i<n; ++i) tot = 1ll * tot * k % MOD;
} void solve() {
  long long ans = 0;

  if (k == 2) for (int i=x+1; i<=n; ++i) ans += get_longer_cnt_k2(i);
  else for (int i=x+1; i<=n; ++i) ans += get_longer_cnt(i);

  ans = (ans % MOD + MOD) % MOD;
  printf("%lld\n", ans);
}
