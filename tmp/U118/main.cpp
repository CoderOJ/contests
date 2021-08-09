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


void preInit() { } 
void init() { } 

constexpr int N = 100005;
int n, m, q;
int a[N], b[N];
int c[N], d[N];

void solve()
{
  n = sc.n(); m = sc.n();
  for (int i = 1; i <= n; i++) c[i] = sc.n(); c[0] = c[n]; 
  for (int i = 1; i <= n; i++) a[i] = a[i - 1] + (c[i] ^ c[i - 1]);
  for (int i = 1; i <= m; i++) d[i] = sc.n(); d[0] = d[m]; 
  for (int i = 1; i <= m; i++) b[i] = b[i - 1] + (d[i] ^ d[i - 1]);

  int q = sc.n();
  while (q --> 0) 
  {
    int l1 = sc.n(), l2 = sc.n(), r1 = sc.n(), r2 = sc.n();
    if (r1 < l1) std::swap(l1, r1);
    if (r2 < l2) std::swap(l2, r2);
    printf("%d\n", 
        std::min(b[r2] - b[l2], b[l2] + b[m] - b[r2]) + 
        std::min(a[r1] - a[l1], a[l1] + a[n] - a[r1]));
  }
}
