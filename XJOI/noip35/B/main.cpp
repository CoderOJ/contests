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

#define long long long
constexpr int MOD = 1000000007;
typedef Intm::Intm<MOD> Int;
const int N = 100005;
int n, k;
long a[N], rk[N], t;

Int fac[N], fac_inv[N];
Int nCr(int n, int r) {
  if (r > n || r < 0) { return Int(0); }
  return fac[n] * fac_inv[n-r] * fac_inv[r]; }

void preInit() { 
  fac[0] = fac_inv[0] = 1;
  for (int i = 1; i < N; ++i) {
    fac[i] = fac[i-1] * Int(i);
    fac_inv[i] = fac_inv[i-1] / Int(i); }
} void init() {
  n = sc.n(); k = sc.n(); t = sc.nl();
  rep (i,n) a[i] = rk[i] = sc.nl();
  std::sort(rk, rk+n);
} void solve() {
  // get: return the number of elements that are LOWER OR EQUAL to a
  auto get = [](long a) -> int { return std::upper_bound(rk, rk+n, a) - rk - 1; };
  rep (i,n) {
    Int ans1, ans2;
    { // this one is not chosen
      int too_low = get(a[i] / t);
      int too_high = n - get(a[i]);
      ans1 = nCr(too_low + too_high, k);
    }
    { // this one is chosen
      long new_val = a[i] * t;
      int must_val = get(new_val) - get(a[i]);
      int free_val = n - must_val - 1;
      int free_cho = k - must_val - 1;
      ans2 = nCr(free_val, free_cho);
    }
    printf("%u\n", static_cast<unsigned>(ans1+ans2));
  }
}
