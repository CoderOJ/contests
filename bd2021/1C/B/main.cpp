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


#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 15;
char a[N][N];
int n;

int dp[N][N];
int get_count(int x1, int y1, int x2, int y2) 
{
  memset(dp, 0, sizeof(dp));
  if (a[x1][y1] != '#') 
    dp[x1][y1] = 1;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (a[i][j] != '#')
      {
        if (i > 0) dp[i][j] += dp[i-1][j];
        if (j > 0) dp[i][j] += dp[i][j-1];
      }
  return dp[x2][y2];
}

void preInit() { } 
void init() 
{
  n = sc.n();
  for (int i = 0; i < n; i++)
    sc.next(a[i]);
} 

void solve() 
{
  if (get_count(0, 0, n-1, n-1) == 0) { puts("0"); return; }
  if (1ll * get_count(1, 0, n-1, n-2) * get_count(0, 1, n-2, n-1) ==
      1ll * get_count(1, 0, n-2, n-1) * get_count(0, 1, n-1, n-2)) { puts("1"); return; }
  puts("2");
}
