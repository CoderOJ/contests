#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
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

constexpr int N = 20;
std::pair<int,int> a[N];
std::pair<int,int> b[N];
int n;

int calc() {
  std::sort(b,b+n, [](std::pair<int,int> a, std::pair<int,int> b) {
    return a.second * b.first > b.second * a.first; });
  int ans = 0; int y = 0;
  rep (i,n) {
    ans += (y + y + b[i].second) * b[i].first;
    y += b[i].second; }
  return ans; }

void preInit() { } void init() {
  n = sc.n(); 
  rep (i,n) { 
    int x=sc.n(), y=sc.n();
    a[i] = std::make_pair(x,y); }
} void solve() {
  int ans = 0;
  for (int bt=0; bt<(1<<n); ++bt) {
    std::copy(a, a+n, b);
    rep (j,n) if (bt & (1<<j)) {
      std::swap(b[j].first, b[j].second); } 
    checkMax(ans, calc()); }
  printf("%d", ans / 2);
  puts((ans & 1) ? ".50" : ".00");
}
