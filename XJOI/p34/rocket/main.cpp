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
#define int long long

/** My code begins here **/

constexpr int N = 305;
std::pair<int,int> a[N];
int dp[2][N*N];
int n;

void preInit() { } void init() {
  n = sc.n(); 
  rep (i,n) { 
    int x=sc.n(), y=sc.n();
    if (x > y) { std::swap(x,y); }
    a[i] = std::make_pair(x,y); }
} void solve() {
  std::sort(a,a+n, [](std::pair<int,int> a, std::pair<int,int> b) {
    return a.second * b.first < b.second * a.first; });
  int pos_sum = 0;
  memset(dp,-0x3f,sizeof(dp)); dp[0][0] = 0;
  for (int i=0;i<n;++i) {
    int *pos=dp[(i&1) ^ 1], *pre=dp[(i&1)];
    memset(pos, -0x3f, sizeof(dp[0]));
    for (int x=0; x<=pos_sum; ++x) if (pre[x] >= 0) {
      int y = pos_sum - x;
      checkMax(pos[x + a[i].first], pre[x] + a[i].first*a[i].second + 2*x*a[i].second);
      checkMax(pos[x + a[i].second], pre[x] + a[i].second * (a[i].first + 2*y)); }
    pos_sum += a[i].first + a[i].second; }
 int ans = *std::max_element(dp[n&1], dp[n&1]+pos_sum+1);
 printf("%lld.", ans / 2);
 puts(ans & 1 ? "50" : "00");
}
