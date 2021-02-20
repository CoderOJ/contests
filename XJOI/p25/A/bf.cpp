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

constexpr int N = 50005;
double a[N], ans[N];
int n;

void preInit() { } void init() {
  n = sc.n(); 
  repa (i,n) a[i] = sc.nextDouble();
  a[0] = a[n+1] = 0;
} void solve() {
  repa (i,n) {
    double pos = 1 - a[i-1];
    repi (j,i,n) {
      pos *= a[j];
      ans[j-i+1] += pos * (1-a[j+1]); } 
    if (i == 1) {
      std::cerr << pos << std::endl; } }
  rep (i,n+1) printf("%.12lf\n", ans[i]);
}
