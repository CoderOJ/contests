
#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/range.h"
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

#define in :

std::vector<std::pair<int,int>> build_one(int k) { 
  std::vector<std::pair<int,int>> res;
  k--; int p1l = 2, p1r = p1l+k, p2l = p1r, p2r = p2l+k;
  for (int i in range(p1l, p1r)) { res.push_back({1, i}); }
  for (int i in range(p1l, p1r)) for (int j in range(p2l, p2r)) { res.push_back({i, j}); }
  for (int i in range(p2l, p2r, 2)) { res.push_back({i, i+1}); }
  return res; }

void preInit() { } void init() {
} void solve() {
  int n = sc.n();
  if (n == 1) { puts("YES"); puts("2 1"); puts("1 2"); return; }
  if (n % 2 == 0) { puts("NO");  return; }
  puts("YES");
  int hn = 2*n-1, hm = (hn * n - 1) / 2;
  printf("%d %d\n", hn * 2, hm * 2 + 1);
  printf("%d %d\n", 1, hn+1);
  auto side = build_one(n);
  for (const auto& [u,v] in side) {
    printf("%d %d\n", u, v);
    printf("%d %d\n", u+hn, v+hn); }
}
