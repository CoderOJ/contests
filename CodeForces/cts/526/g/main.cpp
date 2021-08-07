#include "/home/jack/code/creats/Scanner.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

constexpr int N = 100005;
constexpr int B = 20;
int n, q;

struct edge_t
{
  int v, w;
};

struct tree_t
{
  std::vector<edge_t> e[N];
  void add_edge(int u, int v, int w)
  {
    e[u].push_back({v, w});
    e[v].push_back({u, w});
  }

  std::pair<int,int> get_farthest(int u, int f)
  {
    auto res = std::make_pair(0, u);
    for (const auto& [v, w]: e[u]) if (v != f)
    {
      auto v_res = get_farthest(v, u);
      v_res.first += w;
      res = std::max(res, v_res);
    }
    return res;
  }

  int d2root[N], depth[N], p_son[N], fa[N][B];
  void dfs_init_depth(int u, int f)
  {
    fa[u][0] = f;
    for (int i = 0; i + 1 < B; i++)
      fa[u][i + 1] = fa[fa[u][i]][i];
    depth[u] = 0;
    for (const auto& [v, w]: e[u]) if (v != f)
    {
      d2root[v] = d2root[u] + w;
      dfs_init_depth(v, u);
      int v_depth = depth[v] + w;
      if (v_depth > depth[u])
      {
        depth[u] = v_depth;
        p_son[u] = v;
      }
    }
  }

  int len[N];
  void dfs_init_len(int u, int f)
  {
    if (p_son[u] != 0)
      len[p_son[u]] = len[u];
    for (const auto& [v, w]: e[u]) if (v != f)
    {
      len[v] += w;
      dfs_init_len(v, u);
    }
  }

  int id[N][B], top[N];
  std::vector<std::pair<int,int>> chains;
  std::vector<int> chains_psum;
  void init_chains()
  {
    for (int u = 1; u <= n; u++)
      if (p_son[u] == 0)
        chains.emplace_back(len[u], u);
    std::sort(chains.begin(), chains.end());
    std::reverse(chains.begin(), chains.end());
    memset(id, 0x3f, sizeof(id));
    int id_top = 1;
    chains_psum.push_back(0);
    for (auto [value, u] : chains)
    {
      chains_psum.push_back(chains_psum.back() + value);
      while (u != 0 && id[u][0] == 0x3f3f3f3f)
      {
        len[u] = value;
        id[u][0] = id_top;
        u = fa[u][0];
      }
      top[id_top] = u;
      id_top++;
    }
    for (int i = 0; i + 1 < B; i++)
      for (int u = 1; u <= n; u++)
        id[u][i + 1] = std::min(id[u][i], id[fa[u][i]][i]);
  }

  int get_intersect(int u, int kth)
  {
    for (int i = B - 1; i >= 0; i--)
      if (id[u][i] > kth)
        u = fa[u][i];
    return u;
  }

  int query(int u, int kth)
  {
    if (kth > (int)(chains.size()))
      kth = (int)(chains.size());
    if (id[u][0] <= kth) 
      return chains_psum[(size_t)kth];
    int ans1;
    {
      const int r = get_intersect(u, kth - 1);
      ans1 = d2root[u] - d2root[r] + depth[u] + chains_psum[(size_t)kth - 1];
    }
    int ans2;
    {
      const int r = get_intersect(u, kth);
      const int rt = top[id[r][0]];
      ans2 = d2root[u] - d2root[rt] + depth[u] + chains_psum[(size_t)kth] - chains[(size_t)id[r][0] - 1].first;
    }
    return std::max(ans1, ans2);
  }
} t1, t2;

int main()
{
  n = sc.n();
  q = sc.n();
  for (int i = 1; i < n; i++)
  {
    int u = sc.n(), v = sc.n(), w = sc.n();
    t1.add_edge(u, v, w);
    t2.add_edge(u, v, w);
  }

  int r1 = t1.get_farthest(1, 0).second;
  int r2 = t1.get_farthest(r1, 0).second;
  t1.dfs_init_depth(r1, 0);
  t1.dfs_init_len(r1, 0);
  t1.init_chains();
  t2.dfs_init_depth(r2, 0);
  t2.dfs_init_len(r2, 0);
  t2.init_chains();

  int last_ans = 0;
  while (q --> 0)
  {
    int x = sc.n(), y = sc.n();
    x = (x + last_ans - 1) % n + 1;
    y = (y + last_ans - 1) % n + 1;
    last_ans = std::max(t1.query(x, 2 * y - 1), t2.query(x, 2 * y - 1));
    printf("%d\n", last_ans);
  }
  return 0;
}
