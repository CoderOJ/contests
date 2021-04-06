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

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 100005;
constexpr int M = 23;
int a[N], dp[1 << M];
int pre_minor[M], pre[M], suf_minor[M], suf[M], conti_cnt[M][M];
int n, m, k;

void preInit() {}
void init() {
  n = sc.n(); m = sc.n(); k = sc.n();
  for (int i: range(n)) { a[i] = sc.n() - 1; } }

inline void change_bit(int p, int del) {
  if (!del) { return; }
  for (int i=0; i<m; ++i) {
    pre_minor[i] += del * conti_cnt[p][i];
    suf_minor[i] += del * conti_cnt[i][p]; } }

void solve() {
  for (int i: range(n-1)) { conti_cnt[a[i]][a[i+1]]++; } 
  for (int i: range(1,n)) if (a[i] != a[i-1]) { pre[a[i]]++; suf[a[i-1]]++; }

  std::fill(dp, dp+(1<<m), 0x3f3f3f3f); dp[0] = 0;
  for (unsigned int mask=0; mask<(1u<<m)-1; mask++) {
    int pos = std::popcount(mask) + 1;
    for (int i=0; i<m; ++i) if (!(mask & (1<<i))) {
      int vmask = mask | (1 << i); 
      int delta = ( pre_minor[i]
                    + (pre[i] - pre_minor[i]) * k
                    + suf_minor[i] * k
                    - (suf[i] - suf_minor[i]) ) * pos;
      checkMin(dp[vmask], dp[mask] + delta); }

    unsigned int new_mask = mask + 1;
    for (int i=0; i<m; ++i) change_bit(i, ((new_mask>>i)&1) - ((mask>>i)&1) ); }

  /* for (int i=0; i<(1<<m); ++i) {
    see(std::bitset<8>(i), dp[i]); } */

  printf("%d\n", dp[(1u << m) - 1]);
}
