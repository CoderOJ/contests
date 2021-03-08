#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
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

constexpr int N = 200005;
constexpr int M = 75;

std::bitset<M> bit[N];
int a[M], b[M], n, m;

long long pow3(long long x) {
  long long res = 1;
  for ([[maybe_unused]] int i: range(x)) { res *= 3; }
  return res; }

long long eval(const std::bitset<M> mask) {
  long long ans = 0;
  for (int i: range(m)) if (mask[i]) {
    ans += a[i] * pow3(b[i]); }
  return ans; }

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,n) rep (j,m) bit[i][j] = sc.nextChar() - '0'; 
  rep (i,m) { a[i] = sc.nextInt(); b[i] = sc.nextInt(); } 
} void solve() {
  long long ans = 0;
  for (int b: range(1<<n)) {
    std::bitset<M> pos;
    for (int i: range(n)) if (b & (1<<i)) {
      pos ^= bit[i]; }
    checkMax(ans, eval(pos)); }
  printf("%lld\n", ans);
}
