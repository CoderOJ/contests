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


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 1000000007;
constexpr int N = 100005;
using Int = Temps::Intm<MOD>;
char s[N];
size_t slen;
int T;

Int fac[N], ifac[N];

Int binomial(int n, int r) {
  return fac[n] * ifac[r] * ifac[n - r]; }

std::vector<Int> get(size_t n) {
  std::vector<Int> res(N);
  for (size_t i=0; i<n; ++i) res[i] = 0;
  res[n] = 1;
  for (size_t i=n+1; i<N; i++)  {
    res[i] = binomial((int)i-1, (int)n-1) * Int(25).pow(i - n) + res[i-1] * 26; }
  return res; }

std::vector<Int> mem[N];

void preInit()
{
  fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
  for (int i=2; i<N; ++i) {
    fac[i] = fac[i-1] * i;
    ifac[i] = fac[i].inv(); }
}

void init() 
{
  T = sc.n();
  sc.next(s);
  slen = std::strlen(s);
  mem[slen] = get(slen);
} 

void solve() 
{
  while (T--) {
    int opt = sc.n();
    if (opt == 1) {
      sc.next(s); slen = std::strlen(s);
      if (mem[slen].empty()) mem[slen] = get(slen); }
    else { printf("%d\n", static_cast<int>(mem[slen][(size_t)sc.n()])); } }
}
