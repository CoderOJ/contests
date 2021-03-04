#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/base.h"
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
#define int long long

/** My code begins here **/

constexpr int N = 55;

constexpr auto getFib() {
  std::array<int,N> R{1,1};
  for (int i: range(2ll, N)) {
    R[i] = R[i-2] + R[i-1]; }
  return R; }
constexpr auto fib = getFib();

int n, k;

void preInit() { } void init() {
  n = sc.n(); k = sc.nl();
} void solve() {
  Temps::Vector<int> ans;
  int len = n;
  while (len > 0) {
    if (len >= 2 && fib[len - 1] < k) {
      k -= fib[len - 1];
      ans.push_back({n-len+2, n-len+1});
      len -= 2; }
    else {
      ans.push_back(n-len+1);
      len--; } }
  std::ostream_iterator<int> out(std::cout, " ");
  std::copy(ans.begin(), ans.end(), out);
}
