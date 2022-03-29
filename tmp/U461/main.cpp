#include "graph.h"
#include <bits/stdc++.h>

const int N = 205;

int n;

enum struct state_t
{
  tree,
  untree,
  unvis,
};

state_t e[N][N];
int col[N];

bool query_range(int s, int tl, int tr)
{
  std::vector<std::pair<int, int>> es;
  for (int u = 0; u < n; u++)
    for (int v = u + 1; v < n; v++)
    {
      if (e[u][v] == state_t::untree)
        es.emplace_back(u, v);
      else if (e[u][v] == state_t::unvis)
      {
        if (u == s && v >= tl && v < tr)
          es.emplace_back(u, v);
        else if (v == s && u >= tl && u < tr)
          es.emplace_back(u, v);
      }
    }
  return query(std::move(es));
}

std::vector<int> tr[N];
void dfs(int u, int f)
{
  for (int v : tr[u]) if (v != f)
  {
    col[v] = !col[u];
    dfs(v, u);
  }
}

std::vector<int> check_bipartite(int vsize)
{
  n = vsize;

  for (int u = 0; u < n; u++)
    for (int v = 0; v < n; v++)
      e[u][v] = state_t::unvis;

  std::vector<std::pair<int, int>> es;

  std::queue<int> que;
  que.push(0);
  std::vector<int> us;
  for (int i = 1; i < n; i++) us.push_back(i);
  while (!que.empty() && (int)es.size() != (n - 1))
  {
    int u = que.front(); que.pop();
    while (!query_range(u, 0, n))
    {
      int vl = 0, vr = (int)us.size() - 1;
      while (vl < vr)
      {
        int vm = vl + (vr - vl + 1) / 2;
        if (query_range(u, 0, us[vm]))
          vl = vm;
        else 
          vr = vm - 1;
      }
      es.emplace_back(std::min(u, us[vl]), std::max(u, us[vl]));
      e[u][us[vl]] = e[us[vl]][u] = state_t::tree;
      que.push(us[vl]);
      us.erase(us.begin() + vl);
    }
    for (int v = 0; v < n; v++)
      if (e[u][v] == state_t::unvis)
      {
        e[u][v] = state_t::untree;
        e[v][u] = state_t::untree;
      }
  }

  for (const auto &[u, v] : es)
    tr[u].push_back(v), tr[v].push_back(u);
  dfs(0, 0);

  for (const auto &[u, v] : es)
  {
    std::vector<std::pair<int, int>> c;
    for (int u = 0; u < n; u++)
      for (int v = u + 1; v < n; v++)
        if (col[u] != col[v])
          c.emplace_back(u, v);
    for (const auto &[cu, cv] : es)
      c.erase(std::find(c.begin(), c.end(), std::make_pair(cu, cv)));
    c.emplace_back(u, v);
    if (query(std::move(c)))
      return {};
  }

  std::vector<int> res;
  for (int i = 0; i < n; i++)
    if (col[i] == 0)
      res.push_back(i);
  
  return res;
}
