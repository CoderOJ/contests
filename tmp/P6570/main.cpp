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

constexpr int MOD = 1000000007;
constexpr int B = 18;
constexpr int N = 1 << B;
using Int = Temps::Intm<MOD>;
Int a[B + 1][N], cnt[N], inv[B + 1], phi[N + 1];

inline auto popcount(size_t x) {
  return __builtin_popcountll(x); }

void fwt(Int *a) {
  for (size_t i=0; i<B; ++i)
    for (size_t j=0; j<N; ++j)
      if (j & (1 << i))
        a[j] += a[j ^ (1 << i)]; }
void ifwt(Int *a) {
  for (size_t i=0; i<B; ++i)
    for (size_t j=0; j<N; ++j)
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

void preInit() 
{ 
  inv[1] = 1;
  for (int i: range(2, B+1))
    inv[i] = (MOD - MOD / i) * inv[MOD % i];
  for (int i=0; i<N+1; ++i) phi[i] = i;
  for (int i=1; i<N+1; ++i)
    for (int j=i+i; j<N+1; j+=i)
      phi[j] -= phi[i];
} 

void init() 
{
  for ([[maybe_unused]] int i: range(sc.n())) 
    cnt[sc.n()] += 1;
} 

void solve() 
{
  for (size_t i=1; i<N; i++) {
    int pops = popcount(i);
    for (int j=1; pops*j<=B; ++j) {
      a[pops * j][i] += (j%2 ? 1 : -1) * inv[j] * cnt[i]; } }
  for (int i=0; i<=B; ++i) fwt(a[i]);
  for (size_t i=0; i<N; ++i) {
    Int f[B + 1], g[B + 1];
    for (size_t j=0; j<=B; ++j) f[j] = a[j][i];
    exp(f, g, B + 1);
    for (size_t j=0; j<=B; ++j) a[j][i] = g[j]; }
  for (int i=0; i<=B; ++i) ifwt(a[i]);
  Int ans = 0;
  for (size_t i=0; i<N; ++i) ans += phi[i+1] * a[popcount(i)][i];
  std::cout << ans * Int(2).pow(static_cast<int>(cnt[0])) << std::endl;
}
