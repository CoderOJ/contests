#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
// #include "/home/jack/code/creats/range.hpp"
// #include "/home/jack/code/creats/util.hpp"
// #include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
#define INTM_FAST_64 long long 
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/


constexpr int MOD = 998244353;
constexpr int N = 100005;
using Int = Temps::Intm<MOD>;
std::vector<int> e[N];
Int inv[N];
int n;

void preInit() 
{ 
  inv[0] = inv[1] = 1;
  for (int i = 2; i < N; i++)
    inv[i] = inv[MOD % i] * (MOD - MOD / i);
} 

void init() 
{
  n = sc.n();
  for (int i = 1; i < n; i++)
  {
    int u = sc.n(), v = sc.n();
    e[u].push_back(v);
    e[v].push_back(u);
  }
} 

int size[N];
Int dp[N];

void dfs(int u, int f) 
{
  dp[u] = 1;
  size[u] = 1;
  for (int v: e[u]) if (v != f)
  {
    dfs(v, u);
    size[u] += size[v];
    dp[u] *= dp[v];
  }
  Int mul = inv[size[u]];
  if (u != 1)
    for (int v: e[u]) if (v != f)
      mul += (inv[size[u] - size[v]] - inv[size[u]]);
  dp[u] *= mul;
}

void solve() 
{
  dfs(1, 0);
  Int fac_n = 1;
  for (int i = 1; i <= n; i++)
    fac_n *= i;
  std::cout << dp[1] * fac_n << std::endl;
}
