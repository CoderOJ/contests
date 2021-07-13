#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#define INTM_FAST_64 long long
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
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

constexpr int MOD = 998244353;
constexpr int N = 100005;
using Int = Temps::Intm<MOD>;
char s[N];

void solve() 
{
  int n = sc.n(); sc.next(s);
  int zero_cnt = 0, group2_cnt = 0, group2_len=0;
  for (int i=0; i<n; ++i) {
    if (s[i] == '0') {
      group2_cnt += group2_len / 2; group2_len = 0;
      zero_cnt++; }
    else { group2_len++; } }
  group2_cnt += group2_len / 2;
  see(zero_cnt, group2_cnt);
  Int ans1 = 1, ans2 = 1;
  for (int i=1; i<=group2_cnt; i++) 
    ans1 *= (zero_cnt + i), ans2 *= i;
  std::cout << ans1 / ans2 << std::endl;
}
