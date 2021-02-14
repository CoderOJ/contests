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
#define int long long

constexpr int N = 1 << 24;
constexpr int M = 540005;
int a[N], ans[M];
int32_t b[N], n, p3, p4;
int32_t to[M];

void fwt(int32_t a[]) {
	for(int i=0; i<2*n; ++i) rep (j, p4)
    if(j & (1<<i)) a[j] += a[j ^ (1<<i)];
}

void ifwt(int a[]) {
	for(int i=0; i<2*n; ++i) rep (j, p4)
    if(j & (1<<i)) a[j] -= a[j ^ (1<<i)];
}

constexpr int conv[] = {1, 2, 0};
constexpr int conv2[] = {0, 1, 0, 2};

void preInit() { } void init() {
  n = sc.n();
  p3 = 1; rep (i,n) p3 *= 3;
  p4 = 1 << (n * 2);
} void solve() {
  to[0] = (p4 - 1) / 3;
  repa (i,p3 - 1) {
    to[i] = (to[i / 3] << 2) % p4 + conv[i % 3]; }
  rep (i,p3) b[to[i]] = sc.n(); fwt(b);
  rep (i,p4) { a[i] = b[i]; b[i] = 0; }
  rep (i,p3) b[to[i]] = sc.n(); fwt(b);
  rep (i,p4) a[i] *= b[i];
  ifwt(a);
  b[0] = 0;
  repa (i,p4 - 1) {
    b[i] = (b[i >> 2] * 3) % p3 + conv2[i & 3]; }
  rep (i,p4) ans[b[i]] += a[i];
  rep (i,p3) printf("%lld ", ans[i]);
}
