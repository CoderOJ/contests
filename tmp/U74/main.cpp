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
#include "/home/jack/code/creats/Intdm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 100005;
using Int = Temps::Intdm<0>;
Int a[N];
int n;

void preInit() {  } 
void init() 
{
  n = sc.n();
  Int::set_mod(sc.n());
  for (int i = 0; i < n; i++) a[i] = sc.n();
  a[n] = a[0];
} 

void solve() 
{
  const Int fac = Int(26).pow(n) - 1;

  if (fac == 0)
  {
    std::vector<char> s;
    int x = static_cast<int>(a[0]);
    for (int i = 0; i < n; i++)
    {
      s.push_back('a' + x % 26);
      x /= 26;
    }
    std::reverse(s.begin(), s.end());
    for (char c: s) putchar(c);
    return;
  }

  const Int fac_inv = fac.inv();
  for (int i = 0; i < n; i++)
  {
    Int c = (a[i] * 26 - a[i + 1]) * fac_inv;
    putchar('a' + static_cast<int>(c));
  }
}
