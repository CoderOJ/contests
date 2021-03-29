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
  for (int _case: range(T)) {
    int n = sc.n();
    Temps::Vector<int> a(n);
    for (int i: range(n)) { a[i] = sc.n(); }
    int ans = 0;
    for (int i: range(n-1)) {
      int j = std::min_element(a.begin() + i, a.end()) - a.begin() + 1;
      ans += j - i; std::reverse(a.begin() + i, a.begin() + j); }
    printf("Case #%d: %d\n", _case+1, ans);
  }
}
