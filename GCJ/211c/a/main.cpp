#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 35;
int n, k, a[N];
int case_num = 1;

void preInit() { } 
void init() {
  n = sc.n(); k = sc.n();
  for (int i: range(n)) a[i] = sc.n();
  std::sort(a, a+n); } 

void solve() {
  Vector<int> bars { a[0] - 1, k - a[n-1] };
  for (int i=0; i+1<n; ++i) bars.push_back((a[i+1] - a[i]) / 2);
  std::sort(bars.begin(), bars.end(), std::greater<int>());
  int ans1 = bars[0] + bars[1];

  int ans2 = std::max(a[0] - 1, k - a[n-1]);
  for (int i=0; i+1<n; ++i) checkMax(ans2, a[i + 1] - a[i] - 1);

  printf("Case #%d: %.12lf\n", case_num++, 
         1.0 * std::max(ans1, ans2) / k); }
