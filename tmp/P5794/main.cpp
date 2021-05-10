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

constexpr int N = 200005;
int a[N], n;

struct Triple {
  int last, first, id;
  bool operator< (const Triple rhs) const {
    return last != rhs.last ? last < rhs.last : 
           first != rhs.first ? first < rhs.first :
           id < rhs.id; } };
Triple t[N];

void preInit() { } void init() {
  n = sc.n(); sc.n();
  for (int i=0; i<=n; ++i) a[i] = sc.n();
} void solve() {
  for (int i=0; i<=n; ++i) t[i].id = i, t[i].last = a[i];
  std::sort(a, a + n + 1);
  for (int i=0; i<=n; ++i) t[i].first = a[i];
  std::sort(t, t + n + 1);
  int pos = 0; Vector<int> ans;
  for (int i=0; i<n; ++i) { 
    pos = t[pos].id, ans.push_back(a[pos]); }
  std::cout << ans << std::endl;
}
