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
  int n = sc.n(), m = sc.n();
  Poly A(m+1);
  rep (i,n) { 
    int u = sc.n();
    if (u <= m) A[u] -= 4; }
  A[0] = 1;
  A = A.sqrt();
  A[0] = 2;
  A = A.inv();
  A *= Int(2);
  repa (i,m) printf("%u\n", static_cast<unsigned>(A[i]));
}
