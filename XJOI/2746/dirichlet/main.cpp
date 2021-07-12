#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#define INTM_FAST_64 long long
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/


constexpr int MOD = 998244353;
constexpr int N = 18;
constexpr int L = 1 << N;
using Int = Temps::Intm<MOD>;
Int a, b, p[N];
size_t n, l;
Int f[N + 1][L], mu[L], phi[L];

inline auto popcount(size_t x) -> decltype(__builtin_popcountll(x)) {
  return __builtin_popcountll(x); }

void fwt(Int *a) {
  for (size_t i=0; i<n; ++i)
    for (size_t j=0; j<l; ++j)
      if (j & (1 << i))
        a[j] += a[j ^ (1 << i)]; }
void ifwt(Int *a) {
  for (size_t i=0; i<n; ++i)
    for (size_t j=0; j<l; ++j)
      if (j & (1 << i))
        a[j] -= a[j ^ (1 << i)]; }

void ln(const Int *a, Int *b, size_t n) {
  b[0] = 0;
  for (size_t i=1; i<n; ++i) {
    b[i] = a[i] * i;
    for (size_t k=1; k<i; ++k)
      b[i] -= k * a[i - k] * b[k];
    b[i] /= i; } }

void exp(const Int *a, Int *b, size_t n) {
  b[0] = 1;
  for (size_t i=1; i<n; ++i) {
    b[i] = 0;
    for (size_t k=1; k<=i; ++k)
      b[i] += k * a[k] * b[i - k];
    b[i] /= i; } }

void preInit() { } 
void init() 
{
  a = sc.nl(); b = sc.nl(); l = 1 << (n = (size_t)sc.n());
  for (size_t i=0; i<n; ++i) p[i] = sc.n(), sc.n();
} 

void pow(Int a[][L], Int k) {
  for (size_t i=0; i<=n; ++i) fwt(a[i]);
  for (size_t i=0; i<l; ++i) {
    Int f[N + 1], g[N + 1];
    for (size_t j=0; j<=n; ++j) 
      f[j] = a[j][i];
    ln(f, g, n + 1);
    for (size_t j=1; j<=n; ++j)
      g[j] *= k;
    exp(g, f, n + 1);
    for (size_t j=0; j<=n; ++j)
      a[j][i] = f[j]; }
  for (size_t i=0; i<=n; ++i) ifwt(a[i]);
}

void solve() 
{
  for (size_t i=0; i<l; i++) {
    int pops = popcount(i);
    mu[i] = pops % 2 ? -1 : 1;
    phi[i] = 1;
    Int fx2=1, fx1=1;
    for (size_t j=0; j<n; j++) {
      if (i & (1 << j)) {
        phi[i] *= a * (p[j] - 1);
        fx2 *= p[j] * p[j];
        fx1 *= p[j]; } }
    f[pops][i] = fx2 - fx1 + 1; }
  pow(f, b);
  Int ans = 0;
  for (size_t i=0; i<l; ++i) {
    see(i, mu[i], phi[i], f[popcount(i)][i]); 
    ans += mu[i] * phi[i] * f[popcount(i)][i]; }
  std::cout << ans << std::endl;
}
