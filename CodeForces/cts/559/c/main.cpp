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

constexpr int MOD = 1000000007;
constexpr int N = 2005;
constexpr int M = 200005;
using Int = Temps::Intm<Temps::ConstModuler<MOD>>;
std::pair<int,int> p[N];
Int dp[N];
int n, m, k;

Int fac[M], ifac[M];
inline Int ncr(int n, int r) {
  return fac[n] * ifac[r] * ifac[n-r]; }

void preInit() { 
  fac[0] = ifac[0] = 1;
  for (int i: range(1,M)) {
    fac[i] = fac[i-1] * i;
    ifac[i] = fac[i].inv(); }
} void init() {
  n = sc.n(); m = sc.n(); k = sc.n();
  for (int i: range(k)) { p[i] = {sc.n(), sc.n()}; }
} void solve() {
  std::sort(p, p+k);
  for (int i: range(k)) {
    int dx = p[i].first - 1;
    int dy = p[i].second - 1;
    dp[i] = ncr(dx + dy, dx);
    for (int j: range(i)) {
      if (p[j].first <= p[i].first && p[j].second <= p[i].second) {
        int dx = p[i].first - p[j].first;
        int dy = p[i].second - p[j].second;
        dp[i] += dp[j] * ncr(dx + dy, dx); } } 
    dp[i] = Int(0) - dp[i]; }
  Int ans = ncr(n-1 + m-1, n-1);
  for (int i: range(k)) {
    int dx = n - p[i].first;
    int dy = m - p[i].second;
    ans += dp[i] * ncr(dx + dy, dx); }
  std::cout << ans << std::endl;
}
