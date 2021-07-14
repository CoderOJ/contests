#include "/home/jack/code/creats/gpl.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 200005;
long long sum[N], sum2[N];
int a[N], n;

void preInit() { } 
void init() 
{
  n = sc.n();
  for (int i=0; i<n; ++i) a[i] = sc.nextInt();
  for (int i=0; i<n; ++i) sum[i + 1] = sum[i] + a[i];
  for (int i=0; i<n; ++i) sum2[i + 1] = sum2[i] + 1ll * a[i] * (i + 1);
} 

using point_t = std::pair<int, long long>;
point_t stack[N], *top = stack;
inline auto slope(int pos) {
  return stack[pos + 1] - stack[pos]; }
bool valid(int pos) {
  const auto slope0 = slope(pos), slope1 = slope(pos + 1);
  return slope0.second * slope1.first > slope1.second * slope0.first; }

void solve() 
{
  *top++ = std::make_pair(0, 0);
  long long ans = 0;
  for (int i=1; i<=n; ++i) {
    *top++ = std::make_pair(i, sum[i] * i - sum2[i]); 
    while (top - stack >= 3 && !valid(static_cast<int>(top - stack - 3))) {
      top[-2] = top[-1]; top--; }
    logArray(stack, top);
    const auto k = sum[i];
    int l = 0, r = static_cast<int>(top - stack - 1);
    while (l < r) {
      int mid = (l + r) / 2;
      const auto s = slope(mid);
      // see(l, r, mid, s);
      if (s.second > s.first * k) { l = mid + 1; }
      else { r = mid; } }
    const int pos = stack[l].first;
    const auto cur_ans = sum2[i] - sum2[pos] - (sum[i] - sum[pos]) * pos;
    // see(i, k, pos, cur_ans);
    checkMax(ans, cur_ans); }
  std::cout << ans << std::endl;
}
