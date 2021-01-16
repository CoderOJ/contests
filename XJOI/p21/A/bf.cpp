#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 500005;
int a[N]; int n, q;

void preInit() { } void init() {
  n = sc.n(); rep (i,n) a[i] = (sc.nextChar() == 'C' ? 1 : -1);
} void solve() {
  q = sc.n(); while (q--) {
    int l=sc.n()-1, r=sc.n()-1;
    int pos = 0, max_height = 0, ans = 0;
    repi (i,l,r) {
      pos += a[i];
      if (pos < 0) { pos=0; ans++; }
      checkMax(max_height, pos); }
    printf("%d\n", ans + max_height - pos); }
}
