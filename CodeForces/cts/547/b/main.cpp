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

constexpr int N = 200005;
std::vector<std::pair<int,int>> a;
int ans[N], n;

void preInit() { } void init() {
  n = sc.n();
  rep (i,n) a.push_back({sc.n(), i});
} void solve() {
  std::sort(a.begin(), a.end());
  std::set<std::pair<int,int>> inters{{0,n}};
  std::multiset<int> inter_lens{n};
  for (const auto& [v,p]: a) {
    const auto pinter = --inters.upper_bound({p, std::numeric_limits<int>::max()});
    const auto [l,r] = *pinter; inters.erase(pinter);
    int origin_max_len = *inter_lens.rbegin();
    inter_lens.erase(inter_lens.find(r - l));
    inters.insert({l,p}); inters.insert({p+1,r});
    inter_lens.insert(p-l); inter_lens.insert(r-(p+1));
    int now_max_len = *inter_lens.rbegin();
    see(origin_max_len, now_max_len);
    for (int j=origin_max_len; j>now_max_len; j--) {
      ans[j] = v; } }
  std::ostream_iterator<int> out(std::cout, " ");
  std::copy(ans+1, ans+n+1, out);
}
