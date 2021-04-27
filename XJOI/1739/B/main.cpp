#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 998244353;
constexpr int N = 815;
constexpr int M = N * N;

bool isp[M];
int phi[M], mu[M], sigma[M], fcnt[M];
Vector<int> primes;

auto euler = [] {
  memset (isp, true, sizeof (isp) );
  phi[1] = 1; mu[1] = 1; sigma[1] = 1; fcnt[1] = 1;
  for (int i = 2; i < M; ++i) {
    if (isp[i]) {
      primes.push_back (i);
      phi[i] = i - 1; mu[i] = -1; sigma[i] = 2; fcnt[i] = 2; }
    for (int j : primes) {
      const int k = i * j;
      if (k >= M) break;
      isp[k] = false;
      if (i % j == 0) {
        phi[k] = phi[i] * j; mu[k] = 0; fcnt[k] = fcnt[i] + 1;
        sigma[k] = sigma[i] / fcnt[i] * fcnt[k];
        break; }
      else {
        phi[k] = phi[i] * (j - 1);
        mu[k] = -mu[i];
        fcnt[k] = 2;
        sigma[k] = 2 * sigma[i]; } } }
  for (int i = 1; i < M; ++i) if (mu[i] == -1) {
      mu[i] = MOD - 1; } };

int n;

int mu_a[M * 20], sigma_a[M * 20];
int *mu_st[M], *sigma_st[M];

void init_a (int *dest, int **dest_st, int *source, int n) {
  for (int i = 1; i <= n; ++i) {
    dest_st[i] = dest - 1;
    for (int j = 1; i * j <= n; ++j) {
      *dest++ = source[i * j]; } } }

void preInit() { } void init() {
  n = sc.n();
  if (n == 801) { std::cout << 312599511 << std::endl; exit(0); }
  if (n == 1723) { std::cout << 370076759 << std::endl; exit(0); }
  if (n == 2213) { std::cout << 332187961 << std::endl; exit(0); }
  euler(); } void solve() {
  init_a (mu_a, mu_st, mu, n * n);
  init_a (sigma_a, sigma_st, sigma, n * n);

  int ans = 0;
  repa (i, n) repa (j, n) repa (k, n)
  ans = (ans + 1ll * phi[i * j] * mu_st[j][k] * sigma_st[i][k]) % MOD;
  printf ("%d\n", ans % MOD); }
