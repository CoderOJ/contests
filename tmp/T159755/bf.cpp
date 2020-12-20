#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

const int N = 2000005;
int a[N], n;

void preInit() { } void init() {
  n = sc.n(); rep (i,n) a[i] = sc.n();
  repb (i,n-2,0) { checkMin(a[i], a[i+1]); }
} void solve() {
  auto calc = [](int l, int r) -> int {
    int res = 0;
    rep (i,n) {
      int sl = a[i]-1, sr=i;
      checkMax(res, std::min(r,sr) - std::max(l,sl) + 1); }
    return res; };
  long long ans = 0;
  rep (r,n) rep (l,r+1) ans += calc(l,r);
  printf("%lld\n", ans);
}
