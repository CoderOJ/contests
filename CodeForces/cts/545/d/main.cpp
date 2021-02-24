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
#define int long long

/** My code begins here **/

constexpr int N = 100005;
int a[N]; int n;

void preInit() { } void init() {
  n = sc.n(); rep (i,n) a[i] = sc.n();
  std::sort(a, a+n);
} void solve() {
  int pre = 0, pos = 0;
  for (int i=1;;i++) {
    pre += a[pos++];
    while (pos < n && pre > a[pos]) { pos++; }
    if (pos == n) { printf("%lld\n", i); break; } }
}
