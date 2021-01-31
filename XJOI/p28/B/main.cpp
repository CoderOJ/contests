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
constexpr int N = 60;
long n, k;
long nCr[N + 5][N + 5];

void initNCr() {
  rep (i,N + 1) {
    nCr[i][0] = 1;
    repa (j,i) nCr[i][j] = nCr[i-1][j-1] + nCr[i-1][j]; } }
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

void preInit() { initNCr(); } void init() {
  k = sc.n(); n = sc.nextInt();
} void solve() {
  n = (n % k + k) % k;
  if (n % k == 0) { printf("%lld\n", 1ll << k); return; }
  long ans = 0;
  for (int i=1; i<k; ++i) {
    long best = 0;
    for (int j=0; j<k-i; ++j) {
      if (n % gcd(i + j, k - i - j) == 0) {
        checkMax(best, nCr[k - i - 1][j]); } }
    ans += best; }
  printf("%lld\n", ans * 2);
}
