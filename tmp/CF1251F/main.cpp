#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"
#include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

using Polys::Poly;
using Polys::MOD;
constexpr int N = 300005;

int a[N], a_cnt[N], b[5], n, g_n, k;
Poly p[N], ans[5];

Poly power(Poly A, int b) {
  Poly R(1); R[0] = 1;
  for (;b;b>>=1) {
    if (b & 1) { R *= A; }
    A.resize(1 << (A.n + 1));
    Polys::sqrp(A); }
  return R; }

void preInit() { } void init() {
  g_n = n = sc.n(); k = sc.n();
  rep (i,n) { a_cnt[ a[i] = sc.n() ]++; } std::sort(a, a+n); n = std::unique(a, a+n) - a;
  rep (i,k) { b[i] = sc.n(); } std::sort(b, b+k);
} void solve() {
  int a_r = 0, n1=0, n2=0;
  Poly A(2), B(4); A[0]=1; A[1]=2; B[0]=1; B[1]=2; B[2]=1;
  rep (i, k) {
    while (a_r < n && a[a_r] < b[i]) { 
      (a_cnt[a[a_r]] == 1 ? n1 : n2)++; a_r++; }
    ans[i] = power(A, n1) * power(B, n2); }
  int q = sc.n();
  rep (_case, q) {
    std::size_t p = sc.n();
    if (p % 2 == 1) { puts("0"); continue; }
    p /= 2;
    unsigned int res = 0;
    rep (i, k) {
      if (static_cast<int>(p) <= b[i]) { break; }
      std::size_t pos = p - b[i] - 1;
      if (pos < ans[i].size()) { (res += static_cast<int>(ans[i][pos])) %= MOD; } }
    printf("%d\n", res); }
}
