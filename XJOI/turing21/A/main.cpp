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

constexpr int N = 300005;
struct move_t { int d, k; };
move_t a[N];
int n;

void preInit() { } 
void init() 
{
  n = sc.n();
  long long dsum = 0;
  for (int i = 0; i < n; i++)
  {
    a[i].d = sc.nextInt();
    a[i].k = sc.n();
    dsum += a[i].d;
  }
  if (dsum < 0)
    for (int i = 0; i < n; i++)
      a[i].d = -a[i].d;
} 

void solve() 
{
  std::sort(a, a + n, [](auto x, auto y) {
    return x.d * y.k > y.d * x.k;
  });
  long long ans = 0, pos = 0;
  for (int i = 0; i < n; i++)
  {
    ans += (pos + pos + a[i].d) * a[i].k;
    pos += a[i].d;
  }
  printf("%lld\n", ans);
}
