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

bool valid(int state, int n, int m) {
  int first = state >> (n-m+1);
  rep (i,n-m) {
    first <<= 1;
    fist |= ((state>>(n-m-i))&1);
    if ((state >> (n-first-1)
}

void preInit() { } void init() {

} void solve() {
  int n = sc.n(), m = sc.n();
  int lim = (1 << n);
  int ans = 0;
  rep (state, n) {
     
  }
}
