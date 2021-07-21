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

constexpr int N = 2005;
std::vector<int> e[N];
int n, m, lim;

void preInit() {  } 
void init() 
{
  n = sc.n(); m = sc.n(); lim = sc.n();
  for (int i=0; i<m; i++) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} 

void solve() 
{
  std::mt19937 rand(20050610);
  std::set<int> chosen;
  int ans = 0;
  for (int i=0; i<3000000; i++)  {
    int u = rand() % n + 1; 
    if (chosen.count(u)) { chosen.erase(u);
      for (int v: e[u]) if (chosen.count(v)) ans--; }
    else { chosen.insert(u);
      for (int v: e[u]) if (chosen.count(v)) ans++; }
    if (chosen.size() && ans > static_cast<long long>(chosen.size() - 1) * lim) {
      puts("Yes"); return; } }
  puts("No");
}
