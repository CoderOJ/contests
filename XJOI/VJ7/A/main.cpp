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
// #define int long long

/** My code begins here **/

using Array = std::deque<int>;
int n;

Array pos;

void once() {
  Array tmp{std::numeric_limits<int>::min()};
  int flag = 1;
  auto put_front = [&]() { tmp.push_back(pos.front()); pos.pop_front(); };
  auto put_back  = [&]() { tmp.push_back(pos.back());  pos.pop_back();  };
  while (!pos.empty()) {
    if (flag == 1) {
      bool cmp_1 = tmp.back() <= pos.front();
      bool cmp_2 = tmp.back() <= pos.back();
      if (cmp_1 && cmp_2) { pos.front() <= pos.back() ? put_front() : put_back(); }
      else if (cmp_1) { put_front(); }
      else if (cmp_2) { put_back();  }
      else { flag = -flag; } }
    else {
      bool cmp_1 = tmp.back() >= pos.front();
      bool cmp_2 = tmp.back() >= pos.back();
      if (cmp_1 && cmp_2) { pos.front() >= pos.back() ? put_front() : put_back(); }
      else if (cmp_1) { put_front(); }
      else if (cmp_2) { put_back();  }
      else { flag = -flag; } } }
  tmp.pop_front();
  pos = std::move(tmp);
}

void preInit() { } void init() {
  n = sc.n(); 
  for ([[maybe_unused]] int i: range(1,n+1)) { pos.push_back(sc.n()); }
} void solve() {
  int ans = 0;
  while (!std::is_sorted(pos.begin(), pos.end())) {
    once(); ans++; }
  printf("%d\n", ans); 
}
