#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
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

constexpr int MOD = 1000000007;
constexpr int N = 5005;
typedef Temps::Intm<Temps::ConstModuler<MOD>> Int;

struct Poly : public std::vector<Int> {
  using std::vector<Int>::vector;
  Poly operator* (const Poly& B) const {
    Poly C(size() + B.size() - 1);
    for (std::size_t i=0; i<size(); ++i) {
      for (std::size_t j=0;j<B.size(); ++j) {
        C[i+j] += operator[](i) * B[j]; } } 
    return C; } 
  void log() {
    see(size());
    for (const auto& i: *this) {
      i.log(); }
    see("");
  }
};

int a[N], n, m;

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,n) a[i] = sc.n();
} void solve() {
  Int ans = 1;
  rep (i,n) ans *= a[i];
  Poly B{1};
  rep (i,n) B = B * Poly({static_cast<long long>(a[i]), -1ll});
  {
    Int c = 1;
    rep (i,n+1) {
      if (m-i < 0) { break; }
      ans -= c * B[i];
      c /= n; c *= (m-i); }
  }
  printf("%d\n", static_cast<int>(ans));
}
