#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"

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

constexpr int N = 1005;
constexpr int MOD = 2003;
int stir[N][N];
int n, K, L, F;

struct Poly : public std::vector<int> {
  using std::vector<int>::vector;
  Poly multiply(const Poly& rhs) const {
    long long *r = new long long[size() + rhs.size() - 1]();
    for (std::size_t i=0; i<size(); ++i) {
      for (std::size_t j=0; j<rhs.size(); ++j) {
        r[i + j] += at(i) * rhs.at(j); } }
    Poly R(size() + rhs.size() - 1);
    for (std::size_t i=0; i<size()+rhs.size()-1; ++i) {
      R[i] = r[i] % MOD; }
    delete[] r;
    return R; }
  Poly power(int k) {
    Poly R{1}, A(*this);
    for (;k;k>>=1) {
      if (k & 1) { 
        R = R.multiply(A); 
        if (R.size() > MOD) { R.resize(MOD); } }
      A = A.multiply(A);
      if (A.size() > MOD) { A.resize(MOD); } } 
    return R; }
};

int power(int a, int b) {
  int r = 1;
  for (;b;b>>=1) {
    if (b & 1) { (r *= a) %= MOD; }
    (a *= a) %= MOD; }
  return r;
}

void preInit() {} void init() {
  n = sc.n(); K = sc.n(); L = sc.n(); F = sc.n();
  stir[0][0] = 1;
  for (int i=1; i<=F; ++i) {
    for (int j=1; j<=i; ++j) {
      stir[i][j] = (stir[i-1][j-1] + stir[i-1][j] * j) % MOD; } }
} void solve() {
  Poly S(F+1);
  for (int i=0; i<=F; ++i) { S[i] = stir[F][i]; }
  S = S.power(L);

  int inv_K = power(K % MOD, MOD-2);
  int n_down = 1, inv_K_pow = 1, ans = 0;
  for (int k=0; k<(int)S.size(); ++k) {
    ans = (ans + S[k] * n_down % MOD * inv_K_pow) % MOD;
    (n_down *= (n-k) % MOD) %= MOD;
    (inv_K_pow *= inv_K) %= MOD; }
  printf("%d\n",ans);
}
