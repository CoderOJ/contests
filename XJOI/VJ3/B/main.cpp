#include "/home/jack/code/creats/gpl.h"

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

constexpr int N = 300005;
constexpr int M = 1000005;
int a[N], cnt[M], times[M], n;
int ans[N];

void preInit() { 
} void init() {
  scanf("%d", &n);
  rep (i,n) { scanf("%d", &a[i]); cnt[a[i]]++; }
} void solve() {
  std::fill(ans, ans+n+1, std::numeric_limits<int>::max());
  std::sort(a, a+n); ans[0] = std::unique(a, a+n) - a;
  {
    std::vector<int> cost_red_one;
    for (int i=1; i<M; ++i) if (cnt[i]) {
      for (int j=i+i; j<M; j+=i) if (cnt[j]) {
        cost_red_one.push_back(cnt[i]);
        break; } }
    std::sort(cost_red_one.begin(), cost_red_one.end());
    int pre = 0;
    for (const auto& i: cost_red_one) {
      ans[pre + i] = ans[pre] - 1; pre += i; }
  }
  {
    std::vector<int> cost_red_one;
    for (int i=1; i<M; ++i) if (cnt[i]) {
      cost_red_one.push_back(cnt[i]); }
    std::sort(cost_red_one.begin(), cost_red_one.end());
    int pre = 0, last_ans = ans[0] + 1;
    for (const auto& i: cost_red_one) {
      checkMin(ans[pre + i], --last_ans); pre += i; }
  }
  for (int i=0; i<n; ++i) {
    checkMin(ans[i+1], ans[i]); }
  for (int i=0; i<=n; ++i) {
    printf("%d ", ans[i]); }
}
