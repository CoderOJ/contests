
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

const int MOD = 1000000007;
typedef Intm::Intm<MOD> Int;
const int N = 512;
Int dp[N], tmp[N];
int n, l, r;

void preInit() { } void init() { } void solve() {
  n = sc.n(); l = sc.n(); r = sc.n();
  dp[0] = 1;
  rep (i,n) {
    memcpy(tmp, dp, sizeof(dp)); memset(dp, 0, sizeof(dp));
    repi (i,l,r) rep (j,N) {
      dp[i ^ j] += tmp[j]; } }
  printf("%u", static_cast<unsigned>(dp[0]));
}
