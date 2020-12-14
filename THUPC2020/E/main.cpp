#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

typedef unsigned int u32;
const int N = 200505;
const int B = 505;

u32 a[N], pre[B][N];
int n;

void preInit() { } void init() {
  n = sc.n();
  repa (i,n) a[i] = sc.n();
  repa (i, 500) {
    repa (j,n) {
      pre[i][j] = a[j];
      if (j >= i) { pre[i][j] += pre[i][j-i]; } } }
} void solve() {
  int m = sc.n();
  auto getSum = [](int l, int len, int step) -> u32 {
    int ll = l - step, rr = ll + len * step;
    return pre[step][rr] - (ll>0 ? pre[step][ll] : 0); 
  };
  while (m--) {
    int d=sc.n(), l=sc.n(), r=sc.n();
    u32 ans = 0;
    rep (i,d) { ans += getSum(l+i, d, d) * getSum(r+i*d, d, 1); }
    printf("%u\n", ans); }
}
