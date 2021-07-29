#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"
#include "/home/jack/code/creats/pipe.h"

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

using namespace Temps;
constexpr int MOD = 998244353;
constexpr int N = 30;
constexpr int V = 152510;

inline constexpr int test_dec(int a) { return a >= MOD ? a-MOD : a; }
inline constexpr int test_inc(int a) { return a < 0 ? a + MOD : a; }

inline constexpr int power(int a, int b = MOD - 2) {
  int r = 1;
  for (;b;b>>=1) {
    if (b & 1) { r = 1ll * r * a % MOD; }
    a = 1ll * a * a % MOD; }
  return r; }

/**
 * Poly(a,b) => a * x + b
 */
struct Poly {
  int a=0, b=0;
  constexpr Poly() =default;
  explicit constexpr Poly(int a, int b) : a(a), b(b) {}
  
  constexpr Poly operator+ (const Poly rhs) const { 
    return Poly(test_dec(a+rhs.a), test_dec(b+rhs.b)); }
  constexpr Poly operator- (const Poly rhs) const {
    return Poly(test_inc(a-rhs.a), test_inc(b-rhs.b)); }
  constexpr Poly operator* (const Poly rhs) const {
    return Poly((1ll * a * rhs.b + 1ll * b * rhs.a) % MOD, 1ll * b * rhs.b % MOD); }
  constexpr Poly operator/ (const Poly rhs) const {
    if (rhs.b == 0) { return Poly(0, 1ll * a * power(rhs.a) % MOD); }
    int inv_d = power(rhs.b);
    return Poly(1ll * test_inc((1ll * a * rhs.b - 1ll * b * rhs.a) % MOD) * inv_d % MOD * inv_d % MOD, 
                1ll * b * inv_d % MOD); }
  friend std::ostream& operator<< (std::ostream& out, const Poly rhs) {
    out << "(" << rhs.a << "x + " << rhs.b << ")"; return out; }
};

struct Matrix {
  Poly a[N][N]; int n;
  Matrix (int n) : n(n) {}
  Poly det() {
    Poly ans(0,1);
    for (int i=0; i<n; ++i) {
      // std::cout << *this << std::endl;
      bool have_none_zero = false;
      int valid_id = i;
      for (int j=i; j<n; ++j) {
        const Poly& p = a[j][i];
        if (p.a != 0 || p.b != 0) { have_none_zero = true; }
        if (p.b != 0) { valid_id = j; break; } }

      if (!have_none_zero) { return Poly(); }
      if (valid_id != i) { ans.a = MOD-ans.a; ans.b = MOD-ans.b; }
      for (int j=i; j<n; ++j) { std::swap(a[i][j], a[valid_id][j]); }
      ans = ans * a[i][i];
      if (ans.a==0 && ans.b==0) { return ans; }

      for (int j=i+1; j<n; ++j) {
        Poly mul = a[j][i] / a[i][i];
        for (int k=i; k<n; ++k) {
          a[j][k] = a[j][k] - mul * a[i][k]; } } }
    return ans; }
  constexpr const Poly* operator[] (const int id) const { return a[id]; }
  constexpr Poly* operator[] (const int id) { return a[id]; }
  friend std::ostream& operator<< (std::ostream& out, const Matrix& rhs) {
    for (int i=0; i<rhs.n; ++i) {
      for (int j=0; j<rhs.n; ++j) {
        out << rhs[i][j] << " "; }
    out << "\n"; }
    return out; }
};

int n, m;
struct Edge { int u, v, w; };
Temps::Vector<Edge> e;

int get_val(int thr) {
  int valid_cnt = e | ranges::count([thr](const Edge& a) { return a.w % thr == 0; });
  if (valid_cnt < n-1) { return 0; }
  Matrix a(n - 1);
  for (const auto [u,v,w]: e) if (w % thr == 0) {
    a[u][u] = a[u][u] + Poly(w, 1);
    a[u][v] = a[u][v] - Poly(w, 1);
    a[v][u] = a[v][u] - Poly(w, 1);
    a[v][v] = a[v][v] + Poly(w, 1); }
  return a.det().a; }

std::array<int, V> getPhi() {
  std::array<int, V> phi;
  std::array<bool, V> is_p;
  std::fill(is_p.begin(), is_p.end(), true);
  std::vector<int> primes;
  phi[1] = 1;
  for (int i=2; i<V; ++i) {
    if (is_p[i]) { primes.push_back(i); phi[i] = i-1; }
    for (int j: primes) {
      int k = i * j;
      if (k >= V) { break; }
      is_p[k] = false; 
      if (i % j) { phi[k] = phi[i] * (j-1); }
      else { phi[k] = phi[i] * j; break; } } }
  return phi; }
const auto phi = getPhi();

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); e.resize(m);
  for (int i=0; i<m; ++i) {
    e[i].u = sc.n() - 1; e[i].v = sc.n() - 1; e[i].w = sc.n(); }
} void solve() {
  int ans = 0;
  for (int i=1; i<V; ++i) {
    ans = (ans + 1ll * get_val(i) * phi[i]) % MOD; }
  printf("%d\n", ans);
}
