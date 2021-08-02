#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/


constexpr int MOD = 1000000007;
constexpr int N = 3000005;
using Int = Temps::Intm<MOD>;
int n, q;

Int fac[N], ifac[N], inv[N];
Int ans[N][3];

void preInit() 
{ 
  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[0] = inv[1] = 1;
  for (int i=2; i<N; i++) fac[i] = fac[i-1] * i;
  for (int i=2; i<N; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i);
  for (int i=2; i<N; i++) ifac[i] = ifac[i - 1] * inv[i];
}

void init() 
{
  n = sc.n(); q = sc.n();
  ans[1][0] = Int(3 * n - 1) * n * inv[2];
  ans[1][1] = Int(3 * n + 1) * n * inv[2];
  ans[1][2] = Int(3 * n + 3) * n * inv[2];
  for (int i=2; i<=3*n; i++) {
    Int det_10 = ans[i-1][0] * i, det_21 = ans[i-1][1] * i;
    Int tot = fac[3 * n + 1] * ifac[3 * n - i] * inv[i + 1];
    ans[i][0] = (tot - det_10 - det_10 - det_21) * inv[3];
    ans[i][1] = ans[i][0] + det_10;
    ans[i][2] = ans[i][1] + det_21; }
} 

void solve() 
{
  while (q--) {
    int x = sc.n();
    std::cout << ans[x][2] * ifac[x] << std::endl; }
}
