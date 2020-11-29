#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

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
  const int MOD = 1000000007;
  typedef Intm::Intm<MOD> Int;
  const Int sqrt_2(59713600);
  long long n = sc.nlm(MOD-1);
  Int res = ((sqrt_2 + Int(1)).pow(n) - (Int(1) - sqrt_2).pow(n)) / (sqrt_2 * Int(2));
  printf("%u\n", static_cast<unsigned>(res));
}
