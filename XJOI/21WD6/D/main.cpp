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

constexpr int N = 15;
constexpr int M = 105;

double nCr[M][M];
double f[1 << N][M], g[1 << N][M];
int b_cnt[1 << N], b_sum[1 << N];
int n, m, a[N];

void preInit() { 
  rep (i,M) {
    nCr[i][0] = 1; repa (j,i) {
      nCr[i][j] = nCr[i-1][j] + nCr[i-1][j-1]; } }
} void init() {
  n = sc.n(); m = sc.n();
  rep (i,n) a[i] = sc.n();
} void solve() {
  int n_full = (1 << n);

  f[0][0] = 1;
  for (int b=1; b<n_full; ++b) {
    int pos = -1;
    rep (i,n) if (b & (1<<i)) {
      pos = i; b_cnt[b]++; b_sum[b] += a[i]; } 
    int vb = b ^ (1 << pos);
    rep (i,m+1) rep (j,std::min(a[pos]-1, m-i)+1) {
      f[b][i+j] += f[vb][i] * nCr[i+j][j]; } }

  g[0][0] = 1;
  rep (b,n_full) rep (i, m-b_sum[b]) {
    see(b, i);
    if (i+1 <= m-b_sum[b]) { g[b][i+1] += g[b][i] / (n-b_cnt[b]); }
    rep (j,n) if ((b & (1<<j)) == 0 && i+1 >= a[j]) {
      see(g[b][i] * nCr[i][a[j]-1] / (n-b_cnt[b]));
      g[b ^ (1<<j)][i+1 - a[j]] += g[b][i] * nCr[i][a[j]-1] / (n-b_cnt[b]); } }

  double ans = 0;
  rep (b,n_full) if (b_sum[b] <= m) {
    see(g[b][m - b_sum[b]] , f[b ^ (n_full-1)][m - b_sum[b]] , b_cnt[b]);
    ans += g[b][m - b_sum[b]] * f[b ^ (n_full-1)][m - b_sum[b]] * b_cnt[b]; }
  printf("%.12lf\n", ans);
}
