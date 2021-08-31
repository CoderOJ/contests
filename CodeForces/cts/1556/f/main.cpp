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

constexpr int MOD = 1000000007;
constexpr int N = 14;
using Int = Temps::Intm<MOD>;
std::vector<int> bits[1 << N];
Int p[N], prob[N][N], binom[N + 1][N + 1];
int n;

void preInit() {  } 
void init() 
{
  n = sc.n();
  for (int i = 0; i < n; i++) p[i] = sc.n();
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      prob[i][j] = p[i] * (p[i] + p[j]).inv();
  for (int i = 0; i < (1<<n); i++)
  {
    bits[i].reserve(N);
    for (int j = 0; j < n; j++)
      if (i & (1 << j)) bits[i].push_back(j);
  }
  for (int i = 0; i <= N; i++)
  {
    binom[i][0] = 1;
    for (int j = 1; j <= i; j++)
      binom[i][j] = binom[i-1][j-1] + binom[i-1][j];
  }
} 

Int dp[1 << N][N + 1];
void solve() 
{
  dp[0][0] = 1;
  for (int j = 1; j < (1<<n); j++)
    for (int i = 1; i <= (int)bits[j].size(); i++)
      for (int k = j; k; k = (k - 1) & j)
      {
        int pre = j ^ k, cur = k;
        Int t = 1;
        for (int x : bits[pre])
          for (int y : bits[cur])
            t *= prob[y][x];
        dp[j][i] += dp[pre][i - 1] * t;
      }
  for (int i = 1; i < (1<<n); i++)
    for (int j = (int)(bits[i].size()); j >= 1; j--)
      for (int k = j + 1; k <= (int)(bits[i].size()); k++)
        dp[i][j] -= dp[i][k] * binom[k - 1][k - j];
  Int ans = 0;
  for (int cur = 1; cur < (1 << n); cur++)
  {
    int pre = ((1 << n) - 1) ^ cur;
    Int t = 1;
    for (int x : bits[pre])
      for (int y : bits[cur])
        t *= prob[y][x];
    // see(cur, t, dp[cur][1], (int)(bits[cur].size()) * t * dp[cur][1]);
    ans += (int)(bits[cur].size()) * t * dp[cur][1];
  }
  std::cout << ans << std::endl;
}
