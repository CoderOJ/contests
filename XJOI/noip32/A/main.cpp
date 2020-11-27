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

const int N = 100005;
int a[N];
int n;

void
preInit()
{}

void
init()
{
  n = sc.n();
  rep(i, n) a[i] = sc.n();
  std::sort(a, a + n);
}

void
solve()
{
  int ans = 0;
  rep (i,n) ans += a[i];
  repa(i, n - 1) { ans += (a[i] - a[i - 1]) * 2 * i * (n - i); }
  int g = std::__gcd(ans, n);
  printf("%lld %lld\n", ans / g, n / g);
}
