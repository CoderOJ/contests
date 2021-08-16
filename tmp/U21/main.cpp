#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 1000005;
long long cnt[N * 2], sum[N * 2];
int n;

void preInit() {  } 
void init() 
{
  n = sc.n();
  for (int i = 0; i < n; i++)
  {
    int a = sc.n();
    cnt[a + 1] ++;
    sum[a + 1] += a;
  }
  std::partial_sum(cnt, cnt + N * 2, cnt);
  std::partial_sum(sum, sum + N * 2, sum);
} 

void solve() 
{
  auto query = [](int l, int r, int x)
  {
    return (cnt[r] - cnt[l]) * (l / x) +
           (sum[r] - sum[l]) - l * (cnt[r] - cnt[l]);
  };
  long long ans = std::numeric_limits<long long>::max();
  for (int i = 1; i < N; i++)
  {
    long long cur = 0;
    for (int l = 0; l < N; l += i)
      cur += query(l, l + i, i);
    checkMin(ans, cur);
  }
  std::cout << ans << std::endl;
}
