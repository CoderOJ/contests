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

constexpr int N = 65536;
constexpr int MOD = 998244353;
int n, m, x;
int a[N], b[N];

int power(int a, int b) {
  int r = 1;
  for (;b;b>>=1) {
    if (b & 1) { r = 1ll * r * a % MOD; }
    a = 1ll * a * a % MOD; }
  return r; }

inline void checkAdd(int& a) { a += a < 0 ? MOD : 0; }
inline void checkSub(int& a) { a -= a >= MOD ? MOD : 0; }

namespace polys {

void dft(int *const a, int n) {
  int len = (1 << n);
  static int rev[N], w[N], last_n = -1;
  if (last_n != n) { last_n = n;
    rev[0] = 0;
    for (int i=1; i<len; ++i) {
      rev[i] = (rev[i>>1] >> 1) | ((i&1) << (n-1)); }
    for (int i=0; i<n; ++i) {
      int p = 1 << i; int pw = power(3, (MOD-1) / p / 2); w[p] = 1;
      for (int j=p+1; j<p+p; j++) { w[j] = 1ll * w[j-1] * pw % MOD; } } }
  for (int i=0; i<len; ++i) if (i < rev[i]) { std::swap(a[i], a[rev[i]]); }
  for (int l=1; l<len; l<<=1) {
    for (int i=0; i<len; i+=2*l) {
      for (int j=0; j<l; ++j) {
        int t = 1ll * a[i + l + j] * w[l + j] % MOD;
        checkAdd(a[i + l + j] = a[i + j] - t);
        checkSub(a[i + j] += t); } } }
}

void idft(int *const a, int n) {
  int len = 1 << n;
  std::reverse(a+1, a+len);
  dft(a, n);
  int inv_len = power(len, MOD-2);
  for (int i=0; i<len; ++i) {
    a[i] = 1ll * a[i] * inv_len % MOD; } }

void mulp(int *const a, int *const b, int _n) {
  int l=1, n=0;
  while (l < 2*_n-1) { l *= 2; n++; }
  dft(a, n); dft(b, n);
  for (int i=0; i<l; ++i) { a[i] = 1ll * a[i] * b[i] % MOD; }
  idft(a, n);
}
 
}

int fac[N], ifac[N];

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); x = sc.n();
  for (int i=0; i<=m; ++i) { a[i] = sc.n(); }
  fac[0]=ifac[0]=1; for (int i=1;i<=m;++i) { fac[i] = 1ll * fac[i-1] * i % MOD; ifac[i] = power(fac[i], MOD-2); }
} void solve() {
  for (int i=0; i<=m; ++i) { a[i] = 1ll * a[i] * ifac[i] % MOD; }
  for (int i=0; i<=m; ++i) { b[i] = ifac[i]; if (i % 2) { b[i] = MOD - b[i]; } }
  polys::mulp(a, b, m+1);
  int ans = 0;
  int x_pow = 1, n_down = 1;
  for (int i=0; i<=m; ++i) {
    ans = (ans + 1ll * a[i] * x_pow % MOD * n_down) % MOD;
    x_pow = 1ll * x_pow * x % MOD; n_down = 1ll * n_down * (n-i) % MOD; }
  printf("%d\n", ans);
}
