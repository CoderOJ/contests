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

constexpr int N = 1 << 18;
uint64_t a[N], o[N];
size_t n;

void preInit() 
{ 
} 

void init() 
{
  n = sc.n();
  for (size_t i = 0; i < n; i++)
    o[i] = a[i] = sc.nl();
  std::sort(a, a + n, std::greater<uint64_t>()); 
} 

std::map<uint64_t, uint64_t> ans;
constexpr uint64_t mask = 1ull << 63;



void solve() 
{
  for (size_t i = 0; i < n; i++)
    if ((a[i] & mask) == 0)
    {
      uint64_t ai = a[i] | mask;
      for (size_t j = i; j < n; j++)
        if ((ai & a[j]) == 0)
        {
          ans[a[i]] = a[j];
          ans[a[j]] = a[i];
          a[j] |= mask;
          break;
        }
    }
  for (size_t i = 0; i < n; i++)
    printf("%lu\n", ans[o[i]]);
}
