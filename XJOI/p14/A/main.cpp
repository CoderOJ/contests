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

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

#define long long long

long p, n, MOD;

long power(long a, long b) {
  long res = 1;
  for (;b;b>>=1) {
    if (b & 1) { (res *= a) %= MOD; }
    (a *= a) %= MOD; }
  return res; }
long inv(long a) { return power(a, MOD-2); }

long serie(long n) {
  if (n == 1) { return 1; }
  if (n % 2 == 1) { return (serie(n-1) + power(p, n-1)) % MOD; }
  long h = n / 2;
  return serie(h) * (1 + power(p, h)) % MOD;
}

long calc(long n) {
  if (n == 1) { return 1; }
  if (n % 2 == 1) { return (calc(n-1) + n*power(p, n-1)) % MOD; }
  long h = n / 2;
  return (calc(h) * (1 + power(p, h)) + serie(h) * power(p,h) % MOD * h) % MOD;
}

void preInit() { } void init() {
  p = sc.n(); n = sc.n(); MOD = sc.n();
} void solve() {
  printf("%lld\n", calc(n+1));
}
