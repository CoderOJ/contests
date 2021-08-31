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
#define int long long

/** My code begins here **/

constexpr int N = 1005;
std::pair<int,int> a[N];
int n;

void preInit() {  } 
void init() 
{
  int cur = 0, dir = 1;
  n = sc.n();
  for (int i = 1; i <= n; i++)
  {
    int c = sc.n();
    a[i] = std::make_pair(cur + dir, cur + dir * c);
    cur += dir * c; dir = -dir;
  }
} 

void solve() 
{
  int ans = 0; 
  for (int i = 1; i <= n; i++) if (a[i].first >= a[i].second)
  {
    int gmin = std::numeric_limits<int>::max();
    for (int j = i - 1; j >= 0; j--)
      if (a[j].first <= a[j].second)
      {
        int il = std::max(a[j].first, a[i].second);
        int ir = std::min(a[j].second, a[i].first);
        checkMin(ir, gmin);
        see(j, i, a[j], a[i], il, ir);
        if (ir - il + 1 > 0) ans += ir - il + 1;
        checkMin(gmin, a[j].first);
      }
      else
      {
        checkMin(gmin, a[j].second);
        int il = std::max(a[j].second, a[i].second);
        int ir = std::min(a[j].first, a[i].first);
        checkMin(ir, gmin);
        see(j, i, a[j], a[i], il, ir);
        if (ir - il + 1 > 0) ans += ir - il + 1;
      }
  }
  std::cout << ans << std::endl;
}
