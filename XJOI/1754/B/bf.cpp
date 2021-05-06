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

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

int n, k, x;

int calc(int a[]) {
  logArray(a, a+n);
  int ans = 1;
  int cur = 1;
  for (int i=1; i<n; ++i) {
    cur = a[i] == a[i-1] ? cur + 1 : 1;
    checkMax(ans, cur); }
  return ans; }

int a[50];
int dfs(int index) {
  if (index == n) { return std::max(calc(a) - x, 0); }
  int ans = 0;
  for (int i=0; i<k; ++i) a[index] = i, ans += dfs(index + 1);
  return ans; }

void preInit() { } void init() {
  n = sc.n(), k = sc.n(), x = sc.n();
} void solve() {
  printf("%d\n", dfs(0));  
}
