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

void preInit() { } void init() {
} void solve() {
  long p=sc.n(), n=sc.n(), MOD=sc.n();
  long ans = 0;
  long pow_p = 1;
  rep (i,n+1) {
    (ans += (i+1) * pow_p) %= MOD;
    (pow_p *= p) %= MOD;
  }
  printf("%lld\n", ans);
}