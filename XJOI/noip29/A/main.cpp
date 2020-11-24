#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

typedef Intm::Intm Int;
const int N = 5005;
Int dp[2][N];
Int sum[N];
int n,m,k;

void preInit()
{
  Int::setMod( 19260817 );
}

void init()
{
  n = sc.n(); m = sc.n(); k = sc.n();
  checkMin(k, n);
}

void solve()
{
  dp[0][0] = 1;
  repa (i,m) {
    int _i_1 = (i-1) % 2;
    int _i = i % 2;
    sum[0] = 0;
    repa (j,n+1) sum[j] = sum[j-1] + dp[_i_1][j-1];
    rep (j,n+1) {
      int l = std::max(0, j-k);
      dp[_i][j] = sum[j+1] - sum[l];
    }
  }
  printf("%d\n", static_cast<int>(dp[m%2][n]));
}
