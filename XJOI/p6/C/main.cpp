#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 2005;
std::bitset<N> dp[N];
int n,m,l,s[N];
int c[N], v[N];

void preInit() { } void init() {
  n=sc.n(); l=sc.n();
  rep (i,n) { c[i]=sc.n(); v[i]=sc.n(); }
  m=sc.n(); rep (i,m) s[i]=sc.n();
} void solve() {
  dp[0][0] = 1;
  rep (i,n) repb (j,n,1) {
    repa (k, c[i]) {
      if (k*v[i] > l) { break; }
      dp[j] |= (dp[j-1] << k*v[i]); } }
  std::bitset<N> ans;
  rep (i,m) ans |= dp[s[i]];
  repa (i,l) if (ans[i]) printf("%d ", i);
}
