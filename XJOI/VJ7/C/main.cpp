#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/base.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 998244353;
using Int = Temps::Intm<Temps::ConstModuler<MOD>>;
constexpr int N = 105;
constexpr int M = N * N;
int a[N], n, m, s;
Int b[N], f[M];

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  for (int i: range(n)) { a[i] = sc.n(); } 
  for (int i: range(m)) { b[i] = sc.n(); }
  s = std::accumulate(a, a+n, 0);

} void solve() {
  f[0] = -1ll;
  for (int i: range(n)) {
    for (int j: range(s,a[i]-1,-1)) {
      f[j] -= f[j - a[i]]; } }

  Int ans = n;
  for (int i: range(1,s+1)) {
    for (int j: range(m)) {
      ans += f[i] * b[j] / (b[j] + i); } }
  
  std::cout << ans << std::endl;
}
