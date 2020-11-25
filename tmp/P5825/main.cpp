#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
#include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

void
preInit()
{}

void
init()
{}

void
solve()
{
  using namespace Polys;

  int n = sc.n();
  Poly A(n + 1);
  A[0] = 1;
  repa(i, n) A[i] = A[i - 1] * Int(n + 2 - i) / Int(i);
  repa(i, n) if (i & 1) A[i] = Int() - A[i];
  Poly B(n + 1);
  rep(i, n + 1) B[i] = Int(Helper::power(i + 1, n));
  A *= B;
  rep(i, n + 1) printf("%u ", static_cast<unsigned>(A[i]));
}
