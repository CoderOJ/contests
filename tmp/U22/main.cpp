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
#define INTM_FAST_64 long long
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/


constexpr int MOD = 998244353;
using Int = Temps::Intm<MOD>;
constexpr int N = 1005;
constexpr int W = 5005;
int n, a[N], x;

void preInit() {  } 
void init() 
{
  n = sc.n(); x = sc.n();
  for (int i =  0; i < n; i++) a[i] = sc.n();
  std::sort(a, a + n);
} 

using dp_t = std::pair<int, Int>;
dp_t _dp[2][W], *dp[N];
void solve() 
{
  for (int i = 0; i < N; i++) dp[i] = _dp[i % 2];
  for (int i = 0; i <= x; i++)
    dp[0][i] = std::make_pair(i % a[0], 1);
  for (int i = 1; i < n; i++)
    for (int j = 0; j <= x; j++)
    {
      if (j < a[i])
        dp[i][j] = dp_t(dp[i-1][j].first, dp[i-1][j].second * (i + 1));
      else
      {
        dp_t da = dp[i-1][j % a[i]];
        dp_t db = dp_t(dp[i-1][j].first, dp[i-1][j].second * i);
        if (da.first == db.first)
          dp[i][j] = dp_t(da.first, da.second + db.second);
        else dp[i][j] = std::max(da, db);
      }
    }
  std::cout << dp[n-1][x].first << std::endl;
  std::cout << dp[n-1][x].second << std::endl;
}
