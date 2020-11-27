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

void
preInit()
{}

const int N = 100005;
int a[N];
int n;

void
init()
{
  n = sc.n();
  rep(i, n) a[i] = sc.n();
}

void
solve()
{
  int ans = 0;
  rep(i, n) ans += a[i];
  rep(i, n) rep(j, i)
  {
    int del = abs(a[i] - a[j]);
    ans += del * 2;
  }
  int g = std::__gcd(ans, n);
  printf("%lld %lld\n", ans / g, n / g);
}
