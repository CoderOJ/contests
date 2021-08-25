#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

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

constexpr int N = 60005;
constexpr int MOD = 998244353;
using Int = Temps::Intm<MOD>;
char s[N], t[N];
size_t n;

void preInit() {  } 
void init() 
{
  scanf("%s", s);
  n = strlen(s);
  for (size_t i = 0; i * 2 <= n + 1; i++)
    t[i * 2] = s[i], t[i * 2 + 1] = s[n - i - 1];
} 

Int pre[N], suf[N];
void solve() 
{
  suf[n] = 1;
  for (size_t i = n - 1; i < n; i--)
    suf[i] = suf[i + 1] * (t[i] == '?' ? 26 : 1);

  pre[0] = 1;
  for (size_t i = 1; i < n; i++)
  {
    Int fac = 1;
    for (size_t j = 0; j < i; j++)
    {
      char x = t[i - j - 1], y = t[i + j];
      if (x == '?' && y == '?') fac *= 26;
      else if (x != '?' && y != '?' && x != y) break;
      pre[i + j + 1] += pre[i - j - 1] * fac;
    }
  }

  Int ans = 0;
  for (size_t i = 0; i <= n; i += 2)
    ans += pre[i] * suf[i];
  std::cout << ans << std::endl;
}
