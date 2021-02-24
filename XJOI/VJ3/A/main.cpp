#include "/home/jack/code/creats/gpl.h"

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
#define int long long

/** My code begins here **/

constexpr int N = 200005;
int x[N], y[N], n;
int cnt[2][2][2];

void preInit() { 
#ifndef __LOCALE__
  freopen("integral.in", "r", stdin);
  freopen("integral.out", "w", stdout);
#endif
} void init() {
  scanf("%lld", &n);
  rep (i,n) { scanf("%lld%lld", &x[i], &y[i]); x[i]&=1; y[i]&=1; }
} void solve() {
  x[n] = x[0]; y[n] = y[0];  
  int cur = 0, ans  = 0;
  rep (i,n) {
    cur ^= (x[i] & y[i+1]) ^ (x[i+1] & y[i]);
    rep (a,2) rep (b,2) {
      int csize = (a & y[i+1]) ^ (b & x[i+1]);
      ans += cnt[cur ^ csize][a][b]; }
    cnt[cur][x[i+1]][y[i+1]] ++; }
  printf("%lld\n", cur ? 0 : (ans-n));
}
