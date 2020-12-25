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

constexpr int N = 16;
constexpr int B = 1 << N;
int n, MOD, dp[B][N+1];

int pop_count(int u) {
  int res = 0;
  while (u) {
    res++; u -= u&(-u); }
  return res; }

void preInit() { } void init() {
  n = sc.n(); MOD = sc.n();
} void solve() {
  dp[0][0] = 1;   
  int bits = (1 << n), thr = (n+3) / 4;
  for (int i=1; i<bits; ++i) {
    int id = pop_count(i) - 1;
    for (int j=0; j<n; j++) if ((i>>j) & 1) {
      int pre = i ^ (1<<j);
      bool diff = std::abs(j - id) >= thr;
      for (int k=diff; k<=n; ++k) { (dp[i][k] += dp[pre][k-diff]) %= MOD; } } }
  int res = 0;
  for (int i=(n+1)/2; i<=n; ++i) {
    (res += dp[bits-1][i]) %= MOD; }
  printf("%d\n", res);
}
