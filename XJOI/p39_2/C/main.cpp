#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/util.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
#include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

using Polys::Poly;
using Polys::Int;
constexpr int MOD = 998244353;
constexpr int N = 100005;
int n, m, a[N];
Poly p[N], I;

void preInit() { I.resize(1); I[0] = 1; }
void init() {
  n = sc.n(); m = sc.n();
  for (int i=0; i<n; ++i) { a[i] = sc.n() % MOD; } } 

std::pair<Poly, Poly> mul(int l, int r) {
  if (r - l == 1) { return std::make_pair(I, p[l]); }
  int mid = (l + r + 1) / 2;
  const auto a = mul(l,mid), b = mul(mid,r);
  return std::make_pair(a.first * b.second + b.first * a.second, a.second * b.second); }

void solve() {
  for (int i=0; i<n; ++i) { p[i].resize(2); p[i][0] = 1; p[i][1] = MOD-a[i]; }
  auto ps_frac = mul(0, n); ps_frac.first.resize(m+1); ps_frac.second.resize(m+1);
  auto ps = ps_frac.first * ps_frac.second.inv(); ps.resize(m + 1);
  Poly F(m + 1);
  Polys::Pre::Inv.require(m + 10);
  Int fac_inv = 1;
  for (int i=0; i<=m; ++i) {
    fac_inv *= Polys::Pre::Inv.inv[i+1]; 
    F[i] = fac_inv; }
  const auto G = F.ln();
  for (int i=0; i<=m; ++i) { ps[i] *= G[i]; }
  ps = ps.exp();
  Int fac = 1;
  for (int i=1; i<=m; ++i) {
    fac *= Int(i);
    printf("%d ", static_cast<int>(fac * ps[i])); } }
