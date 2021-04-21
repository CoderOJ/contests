#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
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

constexpr int N = 200005;
std::vector<std::pair<int,int>> l2r[N], r2l[N];
int l[N], r[N], a[N], a2id[N], n;

void construct() {
  std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> que;
  for (int i=1; i<=n; ++i) {
    for (const auto& j: l2r[i]) que.push(j);
    a[que.top().second] = i; a2id[i] = que.top().second; que.pop(); } }

bool change() {
  std::multiset<int> st;
  for (int i=1; i<=n; ++i) {
    see(i, l2r[i]);
    for (const auto& j: l2r[i]) st.insert(a[j.second]);
    st.erase(i);
    int l = ::l[a2id[i]], r = ::r[a2id[i]];
    const auto it = st.lower_bound(l);
    if (it != st.end() && *it <= r) {
      int pa = a2id[*it], pb = a2id[i];
      see(i, pa, pb);
      puts("NO");
      for (int i=0; i<n; ++i)
        printf("%d%c", a[i], " \n"[i==n-1]);
      std::swap(a[pa], a[pb]);
      for (int i=0; i<n; ++i)
        printf("%d%c", a[i], " \n"[i==n-1]);
      return true; }
    st.insert(i);
    for (const auto&  j: r2l[i]) st.erase(a[j.second]);
  }
  return false; }

void preInit() { } void init() {
  n = sc.n();
  for (int i: range(n)) {
    l[i] = sc.n(); r[i] = sc.n();
    l2r[l[i]].push_back({r[i], i}); r2l[r[i]].push_back({l[i],i}); }
} void solve() {
  construct();
  if (!change()) {
    puts("YES");
    for (int i=0; i<n; ++i)
      printf("%d%c", a[i], " \n"[i==n-1]);  }
}
