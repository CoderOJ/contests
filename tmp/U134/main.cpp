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

constexpr int N = 5005;
int u[N], v[N], id[N];
std::multiset<int> e[N];
int n, m;

void preInit() { } 
void init() 
{
  n = sc.n(); m = sc.n();
  for (int i = 0; i < m; i++) 
  {
    u[i] = sc.n(), v[i] = sc.n(), id[i] = sc.n();
    e[u[i]].insert(v[i]);
    if (id[i] == 0)
      e[v[i]].insert(u[i]);
  }
} 

bool vis[N];
void dfs(int u)
{
  if (vis[u])
    return;
  vis[u] = true;
  for (int v: e[u])
    dfs(v);
}

void solve() 
{
  for (int i = 0; i < m; i++)
  {
    if (id[i] == 1)
      id[i] = 0;
    else
    {
      e[u[i]].erase(e[u[i]].find(v[i]));
      e[v[i]].erase(e[v[i]].find(u[i]));
      memset(vis, 0, sizeof(vis));
      dfs(u[i]);
      if (vis[v[i]])
      {
        e[v[i]].insert(u[i]);
        id[i] = 1;
      }
      else
      {
        memset(vis, 0, sizeof(vis));
        dfs(v[i]);
        assert(vis[u[i]]);
        e[u[i]].insert(v[i]);
        id[i] = 0;
      }
    }
  }
  for (int i = 0; i < m; i++)
    printf("%d\n", id[i]);
}
