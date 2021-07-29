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
#define INTM_FAST_64 long long
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 998244353;
constexpr int N = 600005;
using Int = Temps::Intm<MOD>;
int n, a[N];
Int fac[N * 2], ifac[N * 2];

void preInit() 
{ 
  fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
  for (int i=2; i<N*2; i++) {
    fac[i] = fac[i-1] * i;
    ifac[i] = ifac[MOD % i] * (MOD - MOD / i); }
  for (int i=1; i<N*2; i++) ifac[i] *= ifac[i-1];
} 

Int binom(int n, int m) {
  if (m < 0 || m > n) return 0;
  return fac[n] * ifac[n - m] * ifac[m]; }

void init() 
{
  n = sc.n();
  for (int i=0; i<n; i++) a[i] = sc.n();
} 

void solve() 
{
  Int ans = 0;
  int pre_max = 0;
  auto calc = [](int dx, int dy) {
    see(dx, dy);
    return binom(dx + dy + 1, dx + 1) - binom(dx + dy + 1, dx + 2); };
  std::set<int> s(range(1,n+1).begin(), range(1,n+1).end());
  for (int i=0; i<n; i++) {
    checkMax(pre_max, a[i]);
    if (pre_max == n) { break; }
    ans += calc(n - i - 1, n - pre_max - 1); 
    if (a[i] != pre_max && a[i] != *s.begin()) break; 
    s.erase(a[i]); }
  std::cout << ans << std::endl;
}
