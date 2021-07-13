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

using int128_t = __int128_t;
constexpr int N = 2000005;
int n, m, k, a[N];

void preInit() { } 
void init() 
{
  n = sc.n(); m = sc.n(); k = sc.n();
  for (int i=1; i<=n; ++i) a[i] = sc.n();
} 

int128_t dp[N];
int cnt[N];
int pos;

int calc(long long d) {
  pos = 0;
  for (int i=1; i<=n; ++i) {
    if (i > m && dp[i - m] >= dp[pos]) { pos = i - m; }
    dp[i] = a[i] + dp[pos] + d; cnt[i] = cnt[pos] + 1; }
  return cnt[pos = static_cast<int>(std::max_element(dp + 1, dp + n + 1) - dp)]; }

void solve() 
{
  long long l = -1e16, r = 1e16;
  int128_t ans = 0;
  while (l <= r) {
    long long mid = (l + r) / 2;
    if (calc(mid) >= k) { ans = dp[pos] - static_cast<int128_t>(k) * mid; r = mid - 1; }
    else { l = mid + 1; } }
  std::cout << static_cast<int64_t>(ans) << std::endl;
}
