#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
#define int long long

/** My code begins here **/

const int N = 605;
const int M = 105;
const int P = 55;
int n, m, p;
int vol[N];

void
preInit()
{}

void
init()
{
  n = sc.n();
  m = sc.n();
  p = sc.n();
  repa(i, n) vol[i] = sc.nl();
}

int dp[N][P][M];

void
solve()
{
  memset(dp, 0x3f, sizeof(dp));
  memset(dp[0], 0, sizeof(dp[0]));
  vol[0] = vol[1];
  repa(i, n) rep(j, p+1) repa(pos_vol, m)
  {
    if (pos_vol * vol[i] / m == 0) {
      continue;
    }
    repa(pre_vol, m) 
    {
      if (pos_vol == pre_vol) {
        checkMin(dp[i][j][pos_vol],
                 dp[i - 1][j][pre_vol] +
                   abs(vol[i] * pos_vol / m - vol[i - 1] * pre_vol / m));
      } else if (j) {
        checkMin(dp[i][j][pos_vol],
                 dp[i - 1][j - 1][pre_vol] +
                   abs(vol[i] * pos_vol / m - vol[i - 1] * pre_vol / m));
      }
    }
  }
  int ans = 0x3f3f3f3f3f3f3f3f;
  repa (vol, m) checkMin(ans, dp[n][p][vol]);
  printf("%lld\n", ans);
}
