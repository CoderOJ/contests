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

constexpr int N = 1000005;
constexpr int MOD = 998244353;
typedef Intm::Intm<MOD> Int;

Int fac[N], ifac[N], inv[N];

inline Int nCr(int n, int r) { 
  return fac[n] * ifac[r] * ifac[n-r]; }

int n; Int p, q, f[N];
Int pow_p[N], pow_q[N];

void preInit() { 
  fac[0] = fac[1] = inv[0] = inv[1] = ifac[0] = ifac[1] = 1;
  for (int i=2; i<N; ++i) inv[i] = Int(i).inv();
  for (int i=2; i<N; ++i) fac[i] = fac[i-1] * Int(i);
  for (int i=2; i<N; ++i) ifac[i] = ifac[i-1] * inv[i];
} void init() {
  n = sc.n(); p = sc.n(); q = Int(1) - p;
  pow_p[0] = pow_q[0] = 1; repa (i,n) { pow_p[i] = pow_p[i-1] * p; pow_q[i] = pow_q[i-1] * q; }
} void solve() {
  Int i2 = Int(2).inv();
  if (p == i2) {
    for (int i=1; i<n; ++i) {
      printf("%u ", static_cast<unsigned>(nCr(n,i) * i2.pow(1ll*i*(n-i) % (MOD-1)))); } }
  else {
    f[0] = 1;
    for (int i=1; i<n; ++i) {
      f[i] = f[i-1] * (pow_p[n+1-i] - pow_q[n+1-i]) / (pow_p[i] - pow_q[i]); } 
    for (int i=1; i<n; ++i) {
      printf("%u ", static_cast<unsigned>(f[i])); } }
}
