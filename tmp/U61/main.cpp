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

constexpr int B = 20;
constexpr int N = 300005;
std::set<std::pair<int,int>> forbid[N];
std::vector<int> e[N];
int u[N], v[N], w[N];
int n, m, p;

int fa[N][B], dep[N];
void dfs_init(int u, int f)
{
  dep[u] = dep[f] + 1; fa[u][0] = f;
  for (int i = 0; i + 1 < B; i++) fa[u][i + 1] = fa[fa[u][i]][i];
  for (int v: e[u]) dfs_init(v, u);
}
int lca(int u, int v)
{
  if (dep[u] < dep[v]) { std::swap(u, v); }
  int d = dep[u] - dep[v]; for (int i = 0; i < B; i++) if (d & (1 << i)) u = fa[u][i];
  for (int i = B - 1; i >= 0; i--) if (fa[u][i] != fa[v][i]) { u = fa[u][i]; v = fa[v][i]; }
  return u == v ? u : fa[u][0];
}

int id[N], idp[N];
int get_id(int u) { return u == id[u] ? u : id[u] = get_id(id[u]); }
int get_idp(int u) { 
  if (u == 0) return 0;
  return get_id(idp[u]) != get_id(fa[idp[u]][0]) ? idp[u] : idp[u] = get_idp(fa[idp[u]][0]); }

void preInit() { } 
void init() 
{
  n = sc.n(); m = sc.n(); p = sc.n();
  for (int i = 2; i <= n; i++) e[sc.n()].push_back(i);
  for (int i = 0; i < m; i++) u[i] = sc.n(), v[i] = sc.n(), w[i] = sc.n();
  for (int i = 0; i < p; i++) { int id=sc.n()-1, u=sc.n(), v=sc.n(); forbid[id].insert({u, v}); }
} 

void solve() 
{
  dfs_init(1, 0);
  std::vector<int> ids(range(0,m).begin(), range(0,m).end());
  std::sort(ids.begin(), ids.end(), [](int a, int b) { return w[a] < w[b]; });
  for (int i = 1; i <= n; i++) id[i] = idp[i] = i;

  long long ans = 0;
  for (int i: ids) {
    auto merge = [i, &ans](int u, int v)
    {
      u = get_id(u), v = get_id(v);
      if (u == v) return;
      id[u] = v;
      ans += w[i];
    };

    int u = ::u[i], v = ::v[i], l = lca(u, v), d = dep[u] + dep[v] - dep[l] * 2;
    see(u, v, l, d);
    if (d > static_cast<int>(forbid[i].size()) || forbid[i].empty())
    {
      while (true)
      {
        int p = get_idp(u);
        if (dep[p] <= dep[l]) break;
        merge(u, fa[p][0]);
      }
      while (true)
      {
        int p = get_idp(v);
        if (dep[p] <= dep[l]) break;
        merge(v, fa[p][0]);
      }
    }
    else
    {
      std::map<int, int> cnt; cnt[l];
      { int p = u; while (p != l) { cnt[p]; p = fa[p][0]; } }
      { int p = v; while (p != l) { cnt[p]; p = fa[p][0]; } }

      for (auto it = forbid[i].begin(); it != forbid[i].end();)
      {
        const auto [u,v] = *it;
        if (!cnt.count(u) || !cnt.count(v))
          it = forbid[i].erase(it);
        else 
        {
          cnt.at(u)++;
          cnt.at(v)++;
          ++it;
        }
      }

      int min_u = -1, min_occur = std::numeric_limits<int>::max();
      for (const auto& [k,v] : cnt)
        if (checkMin(min_occur, v))
          min_u = k;
      
      std::set<int> uv;
      for (const auto& [u,v] : forbid[i])
      {
        if (u == min_u) uv.insert(v);
        if (v == min_u) uv.insert(u);
      }
      std::map<int,int> discnt;
      for (const auto& [u,v] : forbid[i])
      {
        if (uv.count(u) && !uv.count(v)) discnt[u]++;
        if (uv.count(v) && !uv.count(u)) discnt[v]++;
      }
      int free_cnt = d - static_cast<int>(uv.size());
      for (const auto& [u,v] : discnt) if (v-1 != free_cnt) merge(min_u, u);

      for (const auto& [u,v] : cnt)
        if (!uv.count(u))
          merge(min_u, u);

      for (int u: uv) for (int v: uv)
        if (!forbid[i].count({u,v}) && !forbid[i].count({v,u}))
          merge(u, v);
    }
  }

  printf("%lld\n", ans);
}
