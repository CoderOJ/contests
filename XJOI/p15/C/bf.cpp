#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

#define long long long
long n, k, MOD;

std::unordered_map<long, long> _phi;
long getPhi(long n) {
  if (_phi.count(n)) { return _phi[n]; }
  long res = n, _n=n;
  for (long i=2; i*i<=n; ++i) {
    if (n % i == 0) {
      res = res / i * (i-1);
      while (n % i == 0) { n /= i; } } }
  if (n != 1) { res = res / n * (n-1); }
  return _phi[_n] = res % MOD; }

std::unordered_map<long, long> _mu;
long getMu(long n) {
  if (_mu.count(n)) { return _mu[n]; }
  long res = 1, _n = n;
  for (long i=2; i*i<=n; ++i) {
    if (n % i == 0) {
      res = -res;
      if (n % (i*i) == 0) { return 0; }
      n /= i; } }
  if (n != 1) { res = -res; }
  return _mu[_n] = (res+MOD)%MOD; }

long power(long a, long b) {
  long r = 1;
  for (;b;b>>=1) {
    if (b & 1) (r *= a) %= MOD;
    (a *= a) %= MOD; }
  return r; }

inline long SPhiu(long n, long c) {
  return n%MOD * (c+1)%MOD * getMu(n/c)%MOD; }
long calcSPhi(long n) {
  long res = 0;
  for (long i=1; i*i<=n; ++i) {
    if (n % i == 0) { 
      (res += SPhiu(n, i)) %= MOD;
      if (i * i != n) (res += SPhiu(n, n/i)) %= MOD; } }
  slog("sphi(%lld) = %lld", n, res);
  return res; }

void preInit() { } void init() {
  n = sc.nl(); k = sc.nl(); MOD = sc.nl();
} void solve() {
  long ans = 0;
  for (long i=1; i<=n; ++i) {
    long g = std::__gcd(n,i);
    (ans += power(getPhi(g), k) * ((n * i / g) % MOD)) %= MOD; }
  printf("%lld\n", ans);
}
