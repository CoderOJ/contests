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


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 500005; 
constexpr int W = 1048576;
bool have[W];
int a[N], n;

void preInit() {  } 
void init() 
{
  n = sc.n(); 
  for (int i = 0; i < n; i++) a[i] = sc.n();
} 

void mark(int mask)
{
  if (have[mask]) return;
  have[mask] = 1;
  for (int i = 1; i < W; i <<= 1)
    if (mask & i)
      mark(mask ^ i);
}

void solve() 
{
  int pre_xor = 0;
  for (int i = 0; i < n; i++)
  {
    pre_xor ^= a[i];
    mark(pre_xor);
    int cur = 0;
    for (int i = W/2; i; i >>= 1)
      if ((pre_xor & i) == 0)
        if (have[cur | i])
          cur |= i;
    printf("%d\n", pre_xor + 2 * cur);
  }
}
