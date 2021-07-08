#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 998244353;
constexpr int N = 5005;
using Int = Temps::Intm<MOD>;
Int f[N][N], pow1[N], pow2[N], fac[N], ifac[N];
int n, s;

void preInit() 
{ 
  f[0][0] = 1;
  for (int i=1; i<N; ++i) {
    Int sum=0, ssum=0;
    for (int j=1; j<N; ++j) {
      f[i][j] = ssum;
      sum += f[i-1][j-1];
      ssum += sum; } }
  fac[0] = 1;
  for (int i=1; i<N; ++i)
    fac[i] = fac[i - 1] * i;
  ifac[0] = ifac[1] = 1;
  for (int i=2; i<N; ++i) 
    ifac[i] = (MOD - MOD / i) * ifac[MOD % i];
  for (int i=2; i<N; ++i)
    ifac[i] *= ifac[i-1];
} 

Int nCr(int n, int r) {
  if (r > n || r < 0) { return 0; }
  return fac[n] * ifac[n - r] * ifac[r]; }

void init() 
{
  n = sc.n();
  pow1[0] = pow2[0] = 1;
  pow1[1] = sc.n(); pow2[1] = sc.n();
  for (int i=2; i<=n; ++i)
    pow1[i] = pow1[i-1] * pow1[1], pow2[i] = pow2[i-1] * pow2[1];
  s = sc.n();
} 

void solve() 
{
  Int ans = 0;
  for (int n2=0; n2*2<=n; ++n2) 
    if (n - n2 - s >= 0) {
      ans += nCr(n - n2, n2) * pow2[n2] * pow1[n - n2 * 2] * f[n - n2 - s][n - n2];
    }
  std::cout << ans << std::endl;
}
