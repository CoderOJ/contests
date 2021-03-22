#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
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

constexpr int N = 16;
constexpr int M = (1 << N) + 5;
constexpr int MOD = 1000000007;
using Int = Temps::Intm<Temps::ConstModuler<MOD>>;
int a[N], n, m;

Int fac[M], ifac[M];
inline Int ncr(int n, int r) {
  if (r < 0 || r > n) { return 0; }
  return fac[n] * ifac[n-r] * ifac[r]; }

Int dp[N+1][M];

void preInit() { 
  fac[0] = ifac[0] = 1;
  for (int i: range(1,M)) {
    fac[i] = fac[i-1] * Int(i);
    ifac[i] = fac[i].inv(); }
} void init() {
  n = sc.n(); m = sc.n();
  for (int i: range(m)) a[i] = sc.n();
} void solve() {
  dp[m][0] = 1;  
  for (int i: range(m-1,-1,-1)) {
    for (int j: range(1 << n)) {
      dp[i][j] += dp[i+1][j];
      for (int k: range(n)) if (!(j & (1 << k))) {
        int p = j | (1 << k);
        dp[i][p] += dp[i+1][j] * ncr((1<<n) - j - a[i], (1<<k)-1) * fac[1 << k]; } } }
  for (int i: range(m)) { logArray(dp[i], dp[i]+(1<<n)); }
  Int ans = 0;
  for (int i: range(1 << n)) {
    int pops = 0;
    for (int p=i;p;p -= p&(-p)) { pops++; }
    if (pops % 2 == 1) { ans -= dp[0][i] * fac[(1<<n)-i-1]; }
    else { ans += dp[0][i] * fac[(1<<n) - i - 1]; } }
  std::cout << ans * Int(1<<n) << std::endl;
}
