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
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

#define int long long
constexpr int MOD = 1000000007;
constexpr int N = 1000005;
using Int = Temps::Intm<MOD>;

Int fac[N], ifac[N];
int n, m, g, l;

void preInit() 
{ 
  fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
  for (int i=2; i<N; i++) {
    fac[i] = fac[i - 1] * i;
    ifac[i] = ifac[MOD % i] * (MOD - MOD / i); }
  for (int i=1; i<N; i++) ifac[i] *= ifac[i-1];
} 

Int binom(int n, int r) {
  return fac[n] * ifac[n - r] * ifac[r]; }

void init() 
{
  n = sc.n(); m = sc.n();
  g = Temps::gcd(n, m);
  l = Temps::lcm(n, m);
} 

void solve() 
{
  if (n == 1 && m == 1) { puts("2"); return; }
  if (n == 1 || m == 1) { puts("1"); return; }
  Int ans = 0;
  for (int dx=1,dy=g-1; dx<g && dy>0; dx++,dy--) {
    int num_fill = Temps::lcm(n / Temps::gcd(n,dx), m / Temps::gcd(m,dy));
    see(dx, dy, num_fill);
    if (num_fill * g == n * m) ans += binom(g, dx); }
  std::cout << ans << std::endl;
}
