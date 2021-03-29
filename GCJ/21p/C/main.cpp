#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

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
  int T = sc.n();
  for (int _case: range(1,T+1)) {
    int n = sc.n(), c = sc.n();
    if (c < (n-1) || c >= n*(n+1) / 2) { 
      printf("Case #%d: IMPOSSIBLE\n", _case); }
    else {
      c -= (n-1);
      Temps::Vector<int> a(n);
      for (int i: range(n)) { a[i] = i + 1; }
      for (int i: range(n-2,-1,-1)) {
        int pos = std::min(c, n-i-1); c -= pos;
        std::reverse(a.begin() + i, a.begin() + i + pos + 1); }
      printf("Case #%d: ", _case);
      std::cout << a << std::endl; }
  }
}
