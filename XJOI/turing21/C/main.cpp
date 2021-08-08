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

constexpr int N = 3005;
constexpr int MOD = 1000000007;
using Int = Temps::Intm<MOD>;
Int _dp[N][N * 2], *dp[N];

void preInit() 
{ 
  for (int i = 0; i < N; i++)
    dp[i] = _dp[i] + N;
} 

int a[N], n;
bool neg[N];

void init() 
{
  n = sc.n();
  for (int i = 0; i < n; i++)
  {
    a[i] = sc.nextInt();
    neg[i] = a[i] < 0;
    a[i] = std::abs(a[i]);
  }
  a[n] = 0;
  Temps::dissociate(a, a + n + 1, a);
  for (int i = 0; i < n; i++) 
    if (neg[i])
      a[i] = -a[i];
} 

void solve() 
{
  logArray(a, a + n);
  for (int i = -n; i <= n; i++)
    dp[0][i] = 1;
  for (int i = 0; i < n; i++)
  {
    for (int j = -n; j <= n; j++)
      dp[i + 1][j] = 0;
    int max = -n, min = n;
    int det = 0;
    for (int j = i; j >= 0; j--)
    {
      if (j != i && a[j] != a[j + 1]) {
        int new_det = a[j] < a[j + 1] ? 1 : -1; 
        if (det == 0) det = new_det;
        else if (new_det != det) { break; } }
      checkMax(max, a[j]);
      checkMin(min, a[j]);
      int p1l = min, p1r = max;
      int p2l = -max, p2r = -min;
      if (p1l > p2l) { std::swap(p1l, p2l); std::swap(p1r, p2r); }
      dp[i + 1][p1r] += dp[j][p1l];
      dp[i + 1][p2r] += dp[j][p2l] - dp[j][p1l];
      see(j, i, p1l, p1r, p2l, p2r);
      see(dp[j][p1l], dp[j][p2l]);
    }
    for (int j = -n; j <= n; j++)
      see(i, j, dp[i + 1][j]);
    for (int j = -n; j < n; j++)
      dp[i + 1][j + 1] += dp[i + 1][j];
  }
  std::cout << dp[n][n] << std::endl;
}
