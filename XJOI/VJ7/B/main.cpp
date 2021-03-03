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

constexpr int MOD = 998244353;
constexpr int N = 1000005;
int a[N], n;

typedef Temps::Intm<Temps::ConstModuler<MOD>> Int;
Int fac[N], fac2[N], ifac[N];
inline Int nCr(int n, int r) {
  return fac[n] * ifac[r] * ifac[n-r]; }

void preInit() { 
  fac[0] = ifac[0] = fac2[0] = 1;
  for (int i: range(1,N)) {
    fac[i] = fac[i-1] * i;
    ifac[i] = fac[i].inv();
    fac2[i] = fac2[i-1] * (i * 2 - 1); }
} void init() {
  n = sc.n();
  for (int i: range(n)) a[i] = sc.n(); 
} void solve() {
  Int ans;
  for (int i: range(n)) if (a[i]) {
    ans += fac2[i] * fac2[n-i-1] * nCr(n-1,i); }
  std::cout << ans << std::endl;
}
