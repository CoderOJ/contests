#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 40;
constexpr int MOD = 1000000007;
typedef Temps::Intm<Temps::ConstModuler<MOD>> Int;
constexpr Int I2{2};
Int dp[N][N];
int n;

Int nCr(int n, int k) {
  Int res(1), div(1);
  repa (i,n) res *= i;
  repa (i,k) div *= i;
  repa (i,n-k) div *= i;
  return res / div; }
Int choose_even(int n) {
  Int res(0);
  for (int i=0; i<=n; i+=2) {
    res += nCr(n,i); }
  return res; }

void preInit() { 
  dp[0][0] = 1;
  repa (i,N-1) rep (j,i) repi (k,j,i-1) {
    dp[i][j+1] += dp[k][j] * I2.pow(i-j-1); }
  repa (i,N-1) rep (j,i) { dp[i][j] += dp[i-1][j]; }
} void init() {
  n = sc.n() + 1;
} void solve() {
  Int ans(0);
  int fb = 0; for (;(1<<fb) <= n;++fb);
  std::vector<Int> pre_cho{1};
  repb (i,fb-1,0) {
    rep (i,(int)(pre_cho.size())) {
      pre_cho[i] *= choose_even(i); }
    if (n & (1 << i)) { 
      rep (j,i+1) repi (k,(i!=fb-1), (int)(pre_cho.size()-1)) {
        ans += pre_cho[k] * I2.pow((i-j) * k) * dp[i][j]; }
      pre_cho.push_back(0);
      repb (j,(int)(pre_cho.size()-1), 1+(i!=fb-1)) {
        pre_cho[j] += pre_cho[j-1] / choose_even(j-1); } } }
  std::cout << ans << std::endl;
}
