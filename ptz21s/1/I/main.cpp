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

constexpr int N = 5560;
constexpr int M = N * 2;
std::vector<int> e[N];
int u[M], v[M], n, m;

void preInit() {  } 
void init() 
{
  n = sc.n(); m = sc.n(); 
  for (int i = 0; i < m; i++)
  {
    u[i] = sc.n(), v[i] = sc.n();
    e[u[i]].push_back(v[i]); e[v[i]].push_back(u[i]);
  }
} 

std::pair<int,int> low[N];
int dep[N], size[N];
void dfs0(int u)
{
  low[u] = {u,u};
  size[u] = 1;
  for (int v: e[u]) 
  {
    if (dep[v] == -1) { 
      dep[v] = dep[u] + 1; dfs0(v); size[u] += size[v]; 
      if (dep[low[v].second] < dep[low[u].second])
        low[u] = low[v]; }
    else if (dep[v] + 1 != dep[u] && dep[v] < dep[low[u].second])
      low[u] = {u, v};
  }
}

int eid = 1;
int fa_c[N];
std::vector<int> rc[N];
void dfs1(int u)
{
  std::vector<int> ss;
  for (int v: e[u]) if (dep[v] == dep[u] + 1) ss.push_back(v);
  std::sort(ss.begin(), ss.end(), [](int u, int v) { return size[u] > size[v]; });
  auto rf = rc[u];
  if (rf.size()) rf.erase(std::find(rf.begin(), rf.end(), fa_c[u]));
  for (size_t i = 0; i < std::min(ss.size(), rf.size()); i++)
  {
    fa_c[ss[i]] = rf[i];
    rc[ss[i]] = rc[u];
  }
  for (size_t i = rf.size(); i < ss.size(); i++)
  {
    fa_c[ss[i]] = eid++;
    rc[ss[i]] = rc[u];
    rc[ss[i]].push_back(fa_c[ss[i]]);
  }
  for (int v: e[u]) if (dep[v] == dep[u] + 1) dfs1(v);
}

int ec[M], euc[N];
std::vector<int> ecs[M];
void solve() 
{
  memset(dep, -1, sizeof(dep));  
  dep[1] = 0; dfs0(1); dfs1(1);

  for (int i = 0; i < m; i++)
  {
    int u = ::u[i], v = ::v[i];
    if (dep[u] > dep[v]) std::swap(u, v);
    if (dep[u] + 1 == dep[v]) { ec[i] = fa_c[v]; }
    else ec[i] = eid++;
    if (low[v] == std::make_pair(v,u)) euc[v] = ec[i];
  }
  for (int i = 0; i < m; i++)
  {
    int u = ::u[i], v = ::v[i];
    if (dep[u] > dep[v]) std::swap(u, v);
    ecs[i] = rc[low[v].first];
    ecs[i].push_back(euc[low[v].first]);
  }
  std::cout << Vector<int>(ec, ec + m) << std::endl;
  for (int i = 0; i < m; i++)
    std::cout << ecs[i].size() << " " << ecs[i] << std::endl;
}
