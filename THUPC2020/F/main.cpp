#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

const int N = 305;
int a[N], n, m;
int dp[N][N][2];

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); rep (i,m) a[i] = sc.n();
} void solve() {
  int n1 = (n+1) / 2, n2 = n - n1;
  auto comb = [&](int l1, int l2, int lc, int r1, int r2, int rc) -> bool {
    if (lc == rc && l1 && r1) { return false; }
    if (lc == rc && l2 && r2) { return false; }
    if (l1 + r1 > n1 || l2 + r2 > n2) { return false; }
    return true;
  };
  auto valid = [&](int up, int down, int c) {
    if (c) { return up*2 + down*2 <= n; }
    else { return up*2 + down*2 + 1 <= n; }
  };
}
