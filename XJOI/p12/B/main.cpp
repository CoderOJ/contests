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
constexpr long MOD = 998244353;

void preInit() { } void init() {

} void solve() {
  int n = sc.n(), k = sc.n();
  if (k == 2) { printf("%d\n", n); }
  else if (k == 3) { 
    long upper = n / 2;
    long pre = upper * (upper + 1) % MOD;
    if (n % 2 == 1) { pre += n / 2 + 1; }
    printf("%lld\n", (pre + pre + MOD - n) % MOD); }
}
