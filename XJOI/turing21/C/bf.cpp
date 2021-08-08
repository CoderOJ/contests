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


#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 30;
int a[N], n;

void preInit() 
{ 

} 

void init() 
{
  n = sc.n();
  for (int i = 0; i < n; i++) a[i] = sc.nextInt();
} 

bool on_go(const std::vector<int> &a) {
  int det = 0;
  for (size_t i = 1; i < a.size(); i++)
    if (a[i - 1] != a[i]) 
    {
      int vdet = a[i] > a[i - 1] ? 1 : -1;
      if (det == 0) det = vdet;
      else if (det != vdet) return false;
    }
  return true;
}

bool valid(const std::vector<std::vector<int>> &a) {
  int cur_max = -0x3f3f3f3f;
  for (const auto& x: a) 
  {
    if (!on_go(x)) return false;
    int min = *std::min_element(x.begin(), x.end());
    int max = *std::max_element(x.begin(), x.end());
    int vmax = 0x3f3f3f3f;
    if (min >= cur_max) { checkMin(vmax, max); }
    if (-max >= cur_max) { checkMin(vmax, -min); }
    if (vmax == 0x3f3f3f3f) return false;
    cur_max = vmax;
  }
  see(a);
  return true;
}

void solve() 
{
  int ans = 0;
  for (int i = 0; i < (1 << (n-1)); i++)
  {
    std::vector<std::vector<int>> v;
    v.push_back({a[0]});
    for (int j=0; j<n-1; j++) {
      if (i & (1 << j)) v.push_back({});
      v.back().push_back(a[j + 1]); }
    ans += valid(v);
  }
  std::cout << ans << std::endl;
}
