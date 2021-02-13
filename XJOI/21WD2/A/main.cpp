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

int get(int n) {
  int res = 0;
  res += n / 100; n %= 100;
  res += n / 50 ; n %= 50 ;
  res += n / 10 ; n %= 10 ;
  res += n / 5  ; n %= 5  ;
  res += n / 1  ; n %= 1  ;
  return res; }

int val[500];

void preInit() { } void init() {
  rep (i,500) val[i] = get(i); 
} void solve() {
  long long n = sc.nl();
  int ans = 0;
  rep (i,500) if (val[i] <= n) { ans++; }
  printf("%d\n", ans);
}
