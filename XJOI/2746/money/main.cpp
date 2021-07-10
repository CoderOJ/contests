#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 5005;
int v[N], n, m;

void preInit() 
{ 

} 

void init() 
{
  n = sc.n();
  for (int i=1; i<=n; ++i) v[i] = sc.n();
  for (int i=1; i<n; ++i) sc.n(), sc.n();
  m = sc.n();
  long long s=0, t=0;
  for (int i=0; i<m; ++i) 
    s += v[sc.n()], t += v[sc.n()];
  printf("%lld\n", std::max(s, t));
} 

void solve() 
{

}
