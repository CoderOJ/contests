#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
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
#define int long long

/** My code begins here **/

int n, m, a, b;

int is_pow(int a, int b) {
  int r=1, c=0;
  while (r < b) { r *= a; c++; }
  if (r == b) { return c; }
  else { return -1; } }

std::pair<int,int> make_pow(int a, int b) {
  if (a == 1) { return std::make_pair(1,0); }
  for (int t=2; t*t<=a; ++t) {
    int q = is_pow(t, a);
    if (q != -1) { return std::make_pair(t, b*q); } }
  return std::make_pair(a,b); }

void preInit() { } void init() {
  m = sc.n(); n = sc.n(); a = sc.n(); b = sc.n();
} void solve() {
  std::set<std::pair<int,int>> st;
  for (int i=a; i<a+n; ++i) {
    for (int j=b; j<b+m; ++j) {
      if(st.count(make_pow(i,j))) { see(i,j); }
      st.insert(make_pow(i,j)); } }
  std::cout << st.size() << std::endl;
}
