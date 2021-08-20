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

bool sg[32768][32];
int n, m, s;

void preInit() {  } 
void init() 
{
  n = sc.n(); m = sc.n();
  s = static_cast<int>(std::sqrt(n));
  sg[s + 1][1] = (n - s + 1) % 2;
  for (int i = s; i >= 2; i--)
  {
    int p = 0, v = 1;
    while (v <= n / i) { v *= i; p ++; }
    for (int j = p; j >= 1; j--)
      sg[i][j] = !(sg[i][j + 1] || sg[i + 1][j]);
  }
} 

void solve() 
{
  while (m --)
  {
    int a = sc.n(), b = sc.n();
    if (a <= s) puts(sg[a][b] ? "No" : "Yes");
    else puts((n - a) % 2 ? "Yes" : "No");
  }
}
