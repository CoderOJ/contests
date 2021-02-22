
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

constexpr int N = 20;
char s[N][N]; int n, m, a[N][N];
int sv[N][N], c[N][N];
int dp[1 << N];

inline int lowbit(int u) {
  rep (i,N) if (u & (1 << i)) { return i; } 
  return -1; }

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,n) sc.next(s[i]);
  rep (i,n) rep (j,m) a[i][j] = sc.n();
} void solve() {
  rep (i,n) rep (j,m) {
    int cur_max = 0;
    rep (k,n) if (s[i][j] == s[k][j]) {
      sv[i][j] |= (1 << k);
      c[i][j] += a[k][j]; 
      checkMax(cur_max, a[k][j]); }
    c[i][j] -= cur_max; }
  memset(dp, 0x3f, sizeof(dp)); dp[0] = 0;
  rep (mask, (1<<n)) if (mask) {
    int low = lowbit(mask);
    rep (i,m) { 
      checkMin(dp[mask], dp[mask & (mask ^ sv[low][i])] + c[low][i]);
      checkMin(dp[mask], dp[mask ^ (1 << low)] + a[low][i]); } }
  printf("%d\n", dp[(1<<n) - 1]);
}
