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

#define long long long
constexpr int N = 500005;

struct State { int id1=0, id2=0; long ans=0; };
bool cmp1 (const State& a, const State& b) { return a.id1!=b.id1 ? a.id1<b.id1 : (a.id2!=b.id2 ? a.id2<b.id2 : a.ans<b.ans); }
bool cmp2 (const State& a, const State& b) { return a.id1==b.id1 && a.id2==b.id2; }

std::vector<State> dp[N];
int n, a[N];

void preInit() { } void init() {
  n = sc.n(); a[0] = 0; repa (i,n) a[i] = sc.n();
} void solve() {
  dp[0].push_back(State());
  repa (i,n) {
    for (State& u: dp[i-1]) {
      State v1 = u; if (a[v1.id1] < a[i]) { v1.id1 = i; } else { v1.ans += a[v1.id1] - a[i]; } dp[i].push_back(v1);
      State v2 = u; if (a[v2.id2] < a[i]) { v2.id2 = i; } else { v2.ans += a[v2.id2] - a[i]; } dp[i].push_back(v2); }
    std::sort(dp[i].begin(), dp[i].end(), cmp1);
    dp[i].erase(std::unique(dp[i].begin(), dp[i].end(), cmp2), dp[i].end()); 
  }
  long ans = std::numeric_limits<long>::max();
  for (State& u: dp[n]) checkMin(ans, u.ans);
  printf("%lld\n", ans);
}
