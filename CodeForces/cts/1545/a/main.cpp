#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/


void preInit() 
{ 

} 

void init() 
{

} 

void solve() 
{
  size_t n = (size_t)sc.n();
  std::vector<std::pair<int,int>> a;
  for (size_t i=0; i<n; ++i) 
    a.push_back(std::make_pair(sc.n(), i));
  std::sort(a.begin(), a.end());
  for (size_t l=0,r=0; l<n; l=r) {
    int cnt_src[2]={0,0}, cnt_dest[2]={0,0};
    while (r < n && a[r].first == a[l].first) {
      cnt_src[r % 2]++, cnt_dest[a[r].second % 2]++; r++; }
    if (cnt_src[0] != cnt_dest[0]) { puts("NO"); return; } }
  puts("YES");
}
