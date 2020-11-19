#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

const int N = 10005;
const int K = 55;
int a[N];
int dp[N][K], fr[N][K];
int n, k;


void preInit()
{

}

void init()
{
  n = sc.n(); k = sc.n();
  rep (i,n) a[i] = sc.nextChar() - '0';
}

std::vector <int> borrow;
void trace(int y, int x) {
  // see(y, x);
  if (y == 0 && x == 0) { return; }
  if (fr[y][x] == 0) {
    trace(y-1, x);
  } else {
    trace(y, x-1);
    borrow.push_back(y + x);
  }
}

void solve()
{
  memset(dp, 0x3f, sizeof(dp));
  dp[0][0] = 0;
  for (int i = 1; i <= n+k; ++i) {
    for (int x = 0; x <= k; ++ x) {
      int y = i - x;
      if (y < 0 || y > n) { continue; }
      int sym = i % 10 == 0;
      if (y > 0) {
        if (checkMin(dp[y][x], dp[y-1][x] + sym * a[y-1])) {
          fr[y][x] = 0;
        }
      }
      if (x > 0) {
        if (checkMin(dp[y][x], dp[y][x-1] + sym)) {
          fr[y][x] = 1;
        }
      }
      // see(y, x, sym, dp[y][x]);
    }
  }
  int best_low = 0x3f3f3f3f, best_x = 0;
  for (int i = 0; i <= k; ++ i) {
    if (checkMin(best_low, dp[n][i])) {
      best_x = i;
    }
  }
  printf("%d\n", best_low);
  trace(n, best_x);
  printf("%lu ", borrow.size());
  for (int b: borrow) {
    printf("%d ", b);
  }
}
