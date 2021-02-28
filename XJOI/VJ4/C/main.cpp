#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
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
#define int long long

/** My code begins here **/

constexpr int N = 55;
constexpr int B = 18;
constexpr int W = 1 << 18;
int n,m,k,s,t;
std::vector<int> a;

constexpr std::array<std::array<int,N>,N> genNCr() {
  std::array<std::array<int,N>,N> R{};
  for (int i: range(N)) {
    R[i][0] = 1;
    for (int j: range(1ll,i+1)) { R[i][j] = R[i-1][j-1] + R[i-1][j]; } }
  for (int i: range(N)) {
    for (int j: range(1ll,N)) {
      R[i][j] += R[i][j-1]; } }
  return R; }
constexpr auto nCr = genNCr();
constexpr std::array<int,W> genPops() {
  std::array<int,W> R{};
  for (int i: range(1ll,W)) { R[i] = R[i>>1] + (i&1); }
  return R; }
auto pops = genPops();

int f[W];

int trans(int x) {
  int r=0, r_cnt = 0;
  for (int i: range(B)) { 
    if ((t&(1<<i)) && !(s&(1<<i))) {
      r |= ((x>>i)&1) << (r_cnt++); } }
  return r; }

void preInit() { } void init() {
  n = sc.n(); k = sc.n(); s = sc.n(); t = sc.n();
  if ((s & t) != s || (s | t) != t) { puts("0"); exit(0); }
  m = pops[trans(t)];
  for ([[maybe_unused]] int i: range(n)) {
    int x = sc.n();
    if ((x & s) != s || (x | t) != t) { continue; }
    a.push_back(trans(x)); }
  n = a.size();
} void solve() {
  for (int i: range(1 << m)) {
    std::vector<int> occ;
    for (int j: range(n)) { occ.push_back(i & a[j]); }
    std::sort(occ.begin(), occ.end());
    int l = 0;
    while (l < n) {
      int r = l;
      while (r < n && occ[r] == occ[l]) { r++; }
      f[i] += nCr[r-l][k] - 1;
      l = r; } }
  int ans = 0;
  for (int i: range(1 << m)) {
    ans += (pops[i]%2 ? -1 : 1) * f[i]; } 
  printf("%lld\n", ans);
}
