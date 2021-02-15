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

void preInit() { } void init() {

} void solve() {
  int n = sc.n();
  if (n == 1) { puts("0"); return; }
  if (n == 2) { puts("-1"); return; }
  int k = std::ceil(std::log2(n)) + 1;
  printf("%d\n", k);

  constexpr int pat[] = {2, 2, -1, -3};

  switch (n % 4) {

    case 1:
    case 3:
      rep (i,k) {
        rep (j,n) { printf("%d ", (j+(1<<i))%n + 1); }
        puts(""); } 
      break;

    case 0:
      rep (i,n) { printf("%d ", i + pat[i % 4] + 1); } puts("");
      rep (i,k-1) {
        rep (j,n) { printf("%d ", (j+(1<<i))%n + 1); }
        puts(""); } 
      break;

    case 2:
      rep (i,n-2) { printf("%d ", i + pat[i % 4] + 1); } printf("%d %d\n", n-1, n);
      rep (i,n-4) { printf("%d ", i+1); } printf("%d %d %d %d\n", n-1, n, n-2, n-3);
      rep (i,k-2) {
        rep (j,n) { printf("%d ", (j+(1<<i))%n + 1); }
        puts(""); } 

      break;
  }
}
