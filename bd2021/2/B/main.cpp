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
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 1000000007;
constexpr int N = 3005;
using Int = Temps::Intm<MOD>;
int n, m;

Int dp[N][N];
Int fac[N], ifac[N];
void preInit() 
{  
  fac[0] = 1;
  for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i;
  for (int i = 0; i < N; i++) ifac[i] = fac[i].inv();
  for (int i = 1; i < N; i++)
  {
    dp[i][1] = 1;  
    for (int j = 2; j <= i; j++)
      dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] * j;
  }
  for (int i = 1; i < N; i++)
    for (int j = 1; j < N; j++)
      dp[i][j] *= fac[j];
} 

void init() 
{
  n = sc.n(); m = sc.n();
} 

void solve() 
{
  Int ans = 0;
  for (int i = 1; i <= n; i++)
    ans += dp[n][i] * dp[m][i-1] + dp[n][i] * dp[m][i] * 2 + dp[n][i] * dp[m][i + 1];
  std::cout << ans << std::endl;
}
