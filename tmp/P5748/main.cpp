#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
#include "/home/jack/code/Math/Poly/main.h"
using namespace Polys;

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
  const int n = 100000;
  Pre::Inv.require(n+5);
  Poly A(n+1);
  A[0] = 0;
  Int fac = 1;
  repa (i,n) {
    fac *= Pre::Inv.inv[i];
    A[i] = fac;
  }
  A = A.exp();
  fac = 1;
  repa (i,n) {
    fac *= Int(i);
    A[i] *= fac;
  }
  int t = sc.n();
  rep (i,t) {
    printf("%u\n", static_cast<unsigned>(A[sc.n()]));
  }
}
