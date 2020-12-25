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

// constexpr int N = 200005;
constexpr int M = 1000005;
constexpr int MOD = 1e9 + 7;
typedef Intm::Intm<MOD> Int;
int l[M], r[M], n, m;

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,m) { l[i]=sc.n(); r[i]=sc.n(); }
} void solve() {
  if (n == m) {
    printf("%u\n", static_cast<unsigned>(Int(2).pow(m))); }
  else {
    printf("%u\n", static_cast<unsigned>(Int(2).pow(m) + Int(1))); }
}
