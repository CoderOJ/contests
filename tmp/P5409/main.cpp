#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"

#define POLY_H_MOD 167772161
#define POLY_H_MOD_W 3
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
  int k = sc.n();
  Poly A(n + 1);
  Pre::Inv.require(n + 5);
  A[0] = 0;
  for (int i = 1; i <= n; ++i)
    A[i] = Int(1) * Pre::Inv.inv[i];
  A = A.pow(k, k);
  Int fac=1;
  for (int i = 1; i <= n; ++i) {
    fac *= Int(i);
    A[i] *= fac;
  }
  Int fac_k_inv(1);
  for (int i = 1; i <= k; ++i)
    fac_k_inv *= Pre::Inv.inv[i];
  for (int i = 0; i <= n; ++i)
    printf("%u ", static_cast<unsigned>(A[i] * fac_k_inv));
}
