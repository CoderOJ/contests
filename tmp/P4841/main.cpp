#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"

#define POLY_H_MOD 1004535809
#define POLY_H_MOD_W 3
#include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/


void preInit()
{

}

void init()
{

}

void solve()
{
  using namespace Polys;
  Int N2(2);
  
  int n = sc.n();
  Poly A(n+1);
  A[0] = 1;
  for (int i = 1; i <= n; ++i)
    A[i] = N2.pow( 1ll*i*(i-1)/2 % (POLY_H_MOD-1) );
  Pre::Inv.require(n+5);
  Int fac = 1;
  for (int i = 1; i <= n; ++i)
  {
    fac *= Pre::Inv.inv[i];
    A[i] *= fac;
  }
  A = A.ln();
  printf("%u", static_cast<unsigned>(A[n] / fac));
}
