#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"

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

  int T, n, q; std::cin >> T >> n >> q;
  for ([[maybe_unused]] int _: range(T)) {
    std::vector<int> a{1,2};

    auto query = [&](int a, int b, int c) {
      std::cout << a << ' ' << b << ' ' << c << std::endl;
      int res; std::cin >> res; 
      assert(res != -1);
      return res; };

    for (int i: range(3,n+1)) {
      int l = 0, r = i-1;
      while (l < r) {
        if (l + 1 == r) {
          if (l == 0) {
            if (query(a[l], a[l+1], i) == a[l]) { r = l; break; }
            else { l = r; break; } }
          else {
            if (query(a[l-1], a[l], i) == a[l]) { l = r; break; }
            else { r = l; break; } } }
        int len = (r - l + 1) / 3;
        int m1 = l + len - 1, m2 = l + 2 * len - 1;
        int res = query(a[m1], a[m2], i);
        if (res == a[m1]) { r = m1; }
        else if (res == i) { l = m1 + 1; r = m2; }
        else { l = m2 + 1; } }
      a.insert(a.begin() + l, i); }
    std::cout << a << std::endl;
    int result; std::cin >> result;
  }
}
