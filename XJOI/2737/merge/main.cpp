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

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/


constexpr int N = 100005;
constexpr int W = 60;

int n;
uint64_t a[N], b[N];

int count_bit(uint64_t x) {
  for (int i=1; i<=W; ++i) 
    if ((1ull << i) > x)
      return i;
  std::terminate(); }

void preInit() 
{ 

} 

void init() 
{
  n = sc.n(); sc.n();
  for (int i=0; i<n; ++i) 
    a[i] = (uint64_t)sc.nl();
} 

void solve() 
{
  if (*std::min_element(a, a + n) == 0) {
    puts("0"); return; } 

  uint64_t tot = 0;
  for (int i=0; i<n; ++i) {
    int delta = W - count_bit(a[i]);
    a[i] <<= delta;
    tot += (b[i] = 1ull << delta);
    if (tot >= (1ull << W)) {
      puts("0"); return; } }

  int trim_bits = count_bit(tot) - 1;
  uint64_t least = 1ull << trim_bits;
  uint64_t mask = (1ull << W) - 1;

  for (int b = W-1; b>=0; b--) {
    uint64_t vmask = mask ^ (1ull << b);
    uint64_t vtot = 0;
    for (int i=0; i<n; ++i)
      if ((a[i] & vmask) == a[i])
        vtot += ::b[i];
    if (vtot >= least) 
      mask = vmask; }
  
  printf("%llu\n", (unsigned long long)(mask >> trim_bits));
}
