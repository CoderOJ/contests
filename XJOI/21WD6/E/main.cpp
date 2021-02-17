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

constexpr int N = 20;
constexpr int B_N = (1 << N) - 1;
int n[2], cnt[2][1 << N];
int ans[N];

void preInit() { } void init() {
  n[0] = sc.n(); n[1] = sc.n();
  rep (i,2) rep (j,n[i]) cnt[i][B_N ^ sc.n()]++;
} void solve() {
  rep (i,2) rep (j,N) rep (k,(1<<N)) if (k & (1<<j)) {
      cnt[i][k ^ (1<<j)] += cnt[i][k]; }
  repb (i,N-1,0) { 
    ans[i] = std::numeric_limits<int>::max();
    rep (d,2) for (int j=(1<<i); j<(1<<N); j+=(2<<i)) {
      int cur = cnt[d][j];
      see(i, d, std::bitset<N>(j));
      for (int k=i+1;k<N;++k) if (j & (1<<k)) { cur += ans[k]; }
      checkMin(ans[i], n[d] - cur); } }
  long long tot = 0;
  rep (i,N) tot += static_cast<long long>(ans[i]) << i;
  printf("%lld\n", tot);
}
