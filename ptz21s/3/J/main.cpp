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


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 998244353;
constexpr int N = 105;
using Int = Temps::Intm<MOD>;
std::pair<int,int> a[N]; 
int cnt[N], n, tot_zero;

Int binom[N][N], fac[N];
void preInit() 
{  
  fac[0] = 1;
  for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i;
  for (int i = 0; i < N; i++) {
    binom[i][0] = 1;
    for (int j = 1; j <= i; j++)
      binom[i][j] = binom[i-1][j-1] + binom[i-1][j]; }
} 

void init() 
{
  n = sc.n();
  for (int i = 1; i <= n; i++) a[i].first = sc.n();
  for (int i = 1; i <= n; i++) a[i].second = sc.n();
  std::sort(a + 1, a + n + 1);
  a[n + 1] = std::make_pair(n + 1, n + 1);
  for (int i = 1; i <= n; i++)
    if (a[i].second == 0)
      tot_zero ++, a[i].second = -1;

  for (int i = 0; i <= n; i++) cnt[i] = 1;
  for (int i = 0; i <= n; i++) 
    if (a[i].second != -1)
      cnt[a[i].second] = 0;
  std::partial_sum(cnt, cnt + n + 2, cnt);
} 

Int dp[N][N];
void solve() 
{
  dp[0][0] = 1;
  for (int i = 1; i <= n + 1; i++)
    if (a[i].second != -1)
      for (int k = 0; k <= n; k++)
      {
        int zero_cnt = 0;
        for (int j = i - 1; j >= 0; j--)
        {
          if (a[j].second == -1)
            zero_cnt++;
          else if (a[j].second < a[i].second)
          {
            // see(i, j, cnt[a[i].second], cnt[a[j].second], cnt[a[i].second] - cnt[a[j].second]);
            for (int ck = 0; ck <= std::min({cnt[a[i].second] - cnt[a[j].second], k, zero_cnt}); ck++)
              dp[i][k] += dp[j][k - ck] * binom[zero_cnt][ck] * 
                          binom[cnt[a[i].second] - cnt[a[j].second]][ck];
          }
        }
      }
  Int ans = 0;
  for (int k = 0; k <= tot_zero; k++)
  {
    // see(k, dp[n + 1][k]);
    ans += dp[n + 1][k] * fac[tot_zero - k];
  }
  std::cout << ans << std::endl;
}
