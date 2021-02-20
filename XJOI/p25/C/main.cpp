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

constexpr int N = 100005;
int a[N], n, q;

void preInit() { } void init() {
  n = sc.n(); q = sc.n(); 
  rep (i,n) a[i] = sc.n();
} void solve() {
  while (q--) {
    char opt = sc.nextChar();
    int l=sc.n()-1, r=sc.n()-1;
    if (opt == 'r') { std::reverse(a+l, a+r+1); }
    else {
      long long sum = 0;
      repi (i,l,r) { sum += a[i]; }
      double average = sum / static_cast<double>(r-l+1);
      double ans = 0;
      repi (i,l,r) { ans += (average-a[i]) * (average-a[i]); }
      printf("%.6lf\n", sqrt(ans)); } }
} 
