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
#include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 998244353;
constexpr int N = 1000005;
using Int = Temps::Intm<MOD>;
int n, k, p, a[N];

namespace brute {

constexpr int N = 1000005;
constexpr int M = 1505;
Int _f[M][M], *f[N];
int rmost[N], ans_id[N];

void main() {
  for (int i=0; i<N; ++i) f[i] = _f[i % M];
  for (int l=1; l + 1ll*k*l*(l-1)/2 <= n; ++l) if (a[l % p]) {
    int p = n - 1ll * k * l * (l-1) / 2;
    rmost[p] = l; ans_id[p] = l; }
  for (int i=n-1; i>=0; --i) checkMax(rmost[i], rmost[i + 1]);
  f[0][0] = 1;
  Int ans = 0;
  for (int i=1; i<=n; ++i) {
    int limit = std::min(i, rmost[i]);
    f[i][0] = 0;
    for (int j=1; j<=limit; ++j) f[i][j] = f[i-1][j-1] + f[i-j][j];
    if (ans_id[i]) ans += f[i][ans_id[i]]; }
  std::cout << ans << std::endl; }

} /* namespace brute */

// namespace p23 {

// bool valid() { return k >= n / 4; }

// Int getf(int a, int b) {
//   if (b == 1) { return 1; }
//   if (b == 2) { return a / 2; }
//   Int res = 0;
//   for (int i=1; i*3<=a; ++i) {
//     res += (a - i*3 + 2) / 2; }
//   return res; }

// void main() {
//   Int ans = 0;
//   for (int l=1; l + 1ll*k*l*(l-1)/2 <= n; ++l) if (a[l % p]) {
//     ans += getf(n - 1ll * k * l * (l-1) / 2, l); }
//   std::cout << ans << std::endl; }
// }

namespace k0 {
bool valid() { return k == 0; }
void main() {
  if (a[0] == 0) { puts("0"); return; }
  Polys::Poly A(n + 1);
  Polys::Pre::Inv.require(n + 10);
  for (int i=1; i<=n; ++i) 
    for (int j=i; j<=n; j+=i) 
      A[j] -= Polys::Pre::Inv.inv[j / i];
  A = A.exp().inv();
  std::cout << A[n] << std::endl;
}
} /* namespace k=0 */

void preInit() { } void init() {
#ifndef __LOCALE__
  freopen("partition.in", "r", stdin);
  freopen("partition.out", "w", stdout);
#endif

  n = sc.n(); k = sc.n(); p = sc.n();
  for (int i=0; i<p; ++i) a[i] = sc.n();
} void solve() {
  if (k0::valid()) { k0::main(); return; }
  { brute::main(); return; }
}
