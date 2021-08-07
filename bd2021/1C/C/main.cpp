#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/


void preInit() { } 
void init() { } 
void solve() 
{
  int n = sc.n(), m = sc.n(), x1 = sc.n(), x2 = sc.n();
  int ans = std::numeric_limits<int>::max();
  checkMin(ans, x1 - 1);
  checkMin(ans, x2 - 1 + n - 1);
  checkMin(ans, m - x2);
  checkMin(ans, m - x1 + n - 1);
  checkMin(ans, (n - 1 + (x1 == x2) + std::abs(x1 - x2) - 1) / 2);
  checkMin(ans, n-1);
  checkMin(ans, m-1);
  see(x1 - 1);
  see(x2 - 1 + n - 1);
  see(m - x2);
  see(m - x1 + n - 1);
  see((n - 1 + (x1 == x2) + std::abs(x1 - x2) - 1) / 2);
  see(n-1);
  see(m-1);
  printf("%lld\n", 1ll * ans * ans);
}
