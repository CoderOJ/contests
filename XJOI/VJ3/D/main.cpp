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

constexpr int N = 105;
int a[N], n;
std::vector<int> ans;

bool once_move() {
  int x = n - 1;
  while (x >= 0 && a[x] == x) { x--; }
  if (x < 0) { return false; }
  int y = x - 1;
  while (a[y] != x) { y--; }
  std::swap(a[y], a[(y + a[y]) % n]);
  ans.push_back(y);
  return true;
}

void preInit() { } void init() {
  n = sc.n();
  rep (i,n) a[i] = sc.n();
} void solve() {
  while (once_move());
  printf("%lu\n", ans.size());
  for (const int& i: ans) { printf("%d\n", i); }
}
