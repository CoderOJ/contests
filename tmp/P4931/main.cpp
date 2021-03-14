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

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 998244353;
using Int = Temps::Intm<Temps::ConstModuler<MOD>>;
constexpr int N = 5000005;

Int fac[N], ifac[N], inv[N], f[N], pow2[N];
int n, k;

inline Int nCr(int n, int r) {
  return fac[n] * ifac[r] * ifac[n - r]; }

void preInit() { 
  fac[0] = ifac[0] = pow2[0] = 1;
  inv[1] = 1;
  for (int i: range(2,N)) {
    inv[i] = inv[MOD % i] * (MOD - MOD / i); }
  for (int i: range(1,N)) {
    pow2[i] = pow2[i-1] * 2;
    fac[i] = fac[i-1] * i; ifac[i] = ifac[i-1] * inv[i]; }
  f[0] = 1; f[1] = 0;
  for (int i: range(2,N)) {
    f[i] = Int(4) * i * (i-1) * f[i-1] + Int(8) * i * (i-1) * (i-1) * f[i-2]; }
} void init() {
  n = sc.n(); k = sc.n();
} void solve() {
  Int c = nCr(n,k);
  std::cout << c * c * f[n-k] * pow2[k] * fac[k] << std::endl;
}
