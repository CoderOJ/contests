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

#define MULTIPLE_TEST_CASES_WITH_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 200005;
constexpr int B = 9;
int a[N], n, d[B][N];

void preInit() { } void init() {
  n = sc.n(); rep (i,n) a[i] = sc.n();
} void solve() {
  rep (i,n) {
    unsigned int p = 10;
    rep (b, B) { d[b][i] = a[i] % p; p *= 10; } }
  rep (b,B) std::sort(d[b], d[b] + n);
  long long ans = 0;
  rep (i,n) {
    unsigned int p = 10;
    rep (b,B) {
      int pos = a[i] % p;
      int req = p - pos;
      ans += d[b]+n - std::lower_bound(d[b], d[b]+n, req);
      if (req <= pos) { ans--; } 
      p *= 10; } }
  printf("%lld\n", ans / 2);
}
