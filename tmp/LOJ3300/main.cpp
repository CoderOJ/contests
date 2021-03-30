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
int n, x, p, m;
int a[N], b[N];

int stir[N][N];
void initStir() {
  stir[0][0] = 1;
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= i; ++j) {
      stir[i][j] = (stir[i - 1][j - 1] + 1ll * j * stir[i - 1][j]) % p; } } }

void pow_to_down() {
  for (int i = 0; i <= m; ++i) {
    for (int j = 0; j <= i; ++j) {
      b[j] = (b[j] + 1ll * stir[i][j] * a[i]) % p; } } }

int power(int a, int b) {
  int r = 1;
  for (; b; b >>= 1) {
    if (b & 1) {
      r = 1ll * r * a % p; }
    a = 1ll * a * a % p; }
  return r; }

void preInit() { } void init() {
  n = sc.n(); x = sc.n(); p = sc.n(); m = sc.n();
  for (int i : range(m + 1)) {
    a[i] = sc.n(); } }
void solve() {
  initStir();
  pow_to_down();
  logArray(b, b + n + 1);
  int n_down = 1, x_pow = 1;
  int ans = 0;
  for (int i = 0; i <= m; ++i) {
    ans = (ans + 1ll * n_down * b[i] % p * x_pow % p * power(x + 1, n - i)) % p;
    n_down = 1ll * n_down * (n - i) % p; x_pow = 1ll * x_pow * x % p; }
  printf("%d\n", ans); }
