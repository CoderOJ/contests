#include "/home/jack/code/creats/gpl.h"

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

constexpr int N = 105;
int dp[N][N][N];
char s[1000005]; int w[N], n, k;

void preInit() { } void init() {
  scanf("%s", s); n = std::strlen(s);
  rep (i,n) scanf("%lld", &w[i]);
  scanf("%lld", &k);
} void solve() {
  if (k % 2 == 1 || k > n) { puts("-1"); return; } k /= 2;
  if (k > 1000) { puts("-1"); return; }
  memset(dp, 0x3f, sizeof(dp)); dp[0][0][0] = 0;
  repa (i,n) {
    memcpy(dp[i], dp[i-1], sizeof(dp[i]));
    if (s[i-1] == '(') {
      repa (l,k) rep (r,l) {
        checkMin(dp[i][l][r], dp[i-1][l-1][r] + w[i-1]); } }
    else {
      rep (l,k+1) repa (r,l) {
        checkMin(dp[i][l][r], dp[i-1][l][r-1] + w[i-1]); } } }
  printf("%lld\n", dp[n][k][k]);
}
