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
// #define int long long

/** My code begins here **/

const int N = 1000005;
const int M = 10005;
int n, m;
int ta, a[M], tb, b[M];
int p[N];

void
preInit()
{}

void
init()
{
  memset(a, 0, sizeof(a));
  memset(b, 0, sizeof(b));
  n = sc.n();
  m = sc.n();
  ta = sc.n();
  rep(i, ta) a[sc.n()] = 1;
  tb = sc.n();
  rep(i, tb) b[sc.n()] = 1;
  rep(i, n) p[i] = sc.n();
}

int dp[N];
void
solve()
{
  dp[1] = 0;
  repi(i, 2, m)
  {
    if (a[i] == 1) {
      dp[i] = 0;
      repi(j, 1, i / 2) { checkMax(dp[i], 1 + dp[j] + dp[i - j]); }
    }
    if (b[i] == 1) {
      dp[i] = 0;
      repi(j, 1, i / 2) { checkMin(dp[i], -1 + dp[j] + dp[i - j]); }
    }
  }
  int ans = 0;
  rep(i, n) if (p[i] <= m) ans += dp[p[i]];
  puts(ans > 0 ? "Pomegranate" : "Orange");
}
