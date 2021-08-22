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

constexpr int N = 500005;
int a[N], n;

void preInit() {  } 
void init() 
{
  n = sc.n();
  for (int i = 0; i < n; i++) a[i] = sc.n();
} 

void solve() 
{
  int sum = 0;
  for (int i = 1; i <= n; i++)
  {
    sum ^= a[i - 1]; 
    int x = 0, y = sum, ans = sum;
    for (int j = 0; j < i; j++)
    {
      x ^= a[j]; y ^= a[j];
      checkMax(ans, x + y);
    }
    printf("%d\n", ans);
  }
}
