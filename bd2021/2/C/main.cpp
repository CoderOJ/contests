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
#define int long long

/** My code begins here **/

constexpr int N = 200005;
std::vector<int> e[N];
int n, b[N], p[N];

void preInit() {  } 
void init() 
{
  n = sc.n();
  for (int i = 1; i <= n; i++) e[i].clear();
  for (int i = 1; i < n; i++) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
  for (int i = 1; i <= n; i++) { b[i]=sc.n(); p[i]=sc.n(); }
} 

int dpa[N], dpv[N];
void dfs(int u, int f)
{
  std::vector<int> vvs;
  for (int v: e[u]) if (v != f) { dfs(v,u); vvs.push_back(dpv[v]); }
  int max_sub = 0;
  for (int vv: vvs) { max_sub += std::min(b[u], vv); }
  see(u, max_sub);
  if (max_sub <= b[u] * p[u])
  {
    dpa[u] = b[u] - max_sub;
    dpv[u] = std::min(b[u] * p[u] - max_sub, b[u]);
  }
  else
  {
    dpa[u] = b[u] - b[u] * p[u];
    dpv[u] = 0;
  }
  see(u, b[u], p[u], dpa[u], dpv[u]);
}

void solve() 
{
  dfs(1, 0);
  int ans = 0;
  for (int i = 1; i <= n; i++) ans += dpa[i];
  printf("%lld\n", ans);
}
