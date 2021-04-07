#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
#define long long long

/** My code begins here **/

constexpr int MOD = 998244353;
constexpr int N = 1000005;
constexpr int M = 105;
constexpr int K = 45;

std::array<std::array<int,M>, M> getBinom() {
  std::array<std::array<int,M>, M> R;
  R[0][0] = 1;
  for (int i=1; i<M; ++i) {
    R[i][0] = 1;
    for (int j=1; j<=i; ++j) {
      R[i][j] = (R[i-1][j-1] + R[i-1][j]) % MOD; } }
  return R; }
const auto binom = getBinom();

Temps::Vector<int> getPrime() {
  std::array<bool, N> is_p;
  std::fill(is_p.begin(), is_p.end(), true);
  is_p[1] = false; 
  Temps::Vector<int> primes;
  for (int i=2; i<N; ++i) {
    if (is_p[i]) { primes.push_back(i); }
    for (int j: primes) {
      if (i * j >= M) { break; }
      is_p[i * j] = false;
      if (i % j == 0) { break; } } }
  return primes; }
const auto primes = getPrime();

long n, s;
int dp1[K][K][K], dp2[K][K][K];

void calc(const Temps::Vector<int>& facs, int (*dp)[K][K][K]) {
  memset(*dp, 0, sizeof(*dp)); 
  for (int i=0; i<K; ++i) {
    (*dp)[0][i][i] = 1;
    for (int j=0; j<i; ++j) (*dp)[0][i][j] = 0;
    int p_id = 0;
    for (int p: facs) { 
      for (int k=0; k<=i; ++k) for (int f=k; f<=i; ++f) {
        if (f - k > p) { continue; }
        int r = p - f + k;
        if (k == i && r != 0) { continue; }
        int cur = binom[f][k];
        if (r != 0) { cur = 1ll * cur * binom[r+i-k-1][i-k-1] % MOD; }
        (*dp)[p_id+1][i][k] = ((*dp)[p_id+1][i][k] + 1ll * cur * (*dp)[p_id][i][f]) % MOD; } 
      p_id++; } } }

void preInit() { } void init() {
  n = sc.nl(); s = sc.nl();
} void solve() {

  auto getFactor = [](long n, long m) {
    Temps::Vector<int> a, b;
    for (int p: primes) {
      if (1ll * p * p > n) { break; }
      if (n % p == 0) {
        a.push_back(0); b.push_back(0);
        while (n % p == 0) { n /= p; a.back()++; }
        while (m % p == 0) { m /= p; b.back()++; }
        a.back() -= b.back(); } }
    if (n != 1) { a.push_back(m==1); b.push_back(m!=1); }
    return std::make_pair(a,b); };

  const auto facs = getFactor(n,s);
  calc(facs.first, &dp1); calc(facs.second, &dp2);
  // see(facs);

  int ans = 0;
  int _size = facs.first.size();
  for (int i=0; i<K-2; ++i) {
    for (int j=std::max(0,i-1); j<=i+1; ++j) {
      int cur = 1ll * dp1[_size][i][0] * dp2[_size][j][0] % MOD;
      if (i == j && i != 0) { cur = 2 * cur % MOD; }
      ans = (ans + cur) % MOD; } }
  printf("%d\n", ans);
}
