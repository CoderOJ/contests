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

constexpr int N = 101005;
long long a[N], b[N], n;

bool jury(int up) {
  memcpy(b, a, sizeof(*b) * (n+100)); 
  for (int i=up;i<n; ++i) {
    b[0] += b[i]; b[i] = 0; }
  long long req = 1;
  for (int i=up-1; i>0; i--) {
    if (b[i] < req) { req += req - b[i]; }
    else { b[0] += b[i] - req; }
    if (req >= (long long)(1e17)) { return false; } }
  return req <= b[0];
}

void preInit() { } void init() {
  n = sc.n(); rep (i,n) a[i] = sc.n();
} void solve() {
  long long tot = std::accumulate(a, a+n, 0);
  if (tot == 1) {
    printf("%d\n", std::max(1, (int)(std::max_element(a, a+n) - a)));
    return; }
  int l = 1, r = n + 100;
  while (l < r) {
    int mid = (l + r + 1) / 2;
    if (jury(mid)) { l = mid; }
    else { r = mid - 1; } }
  printf("%d\n", r);
}
