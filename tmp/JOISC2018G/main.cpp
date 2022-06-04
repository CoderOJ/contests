#include "airline.h"
#include <algorithm>
#include <vector>

void Alice(int n, int m, int u[], int v[])
{
  std::vector<std::pair<int, int>> e;
  for (int i = 0; i < m; i++)
    e.emplace_back(u[i], v[i]);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < 10; j++)
      if (i & (1 << j))
        e.emplace_back(i, n + j);
  for (int i = 0; i + 1 < 10; i++)
    e.emplace_back(n + i, n + i + 1);
  e.emplace_back(n + 1, n + 3);
  for (int j = 0; j < 10; j++)
    e.emplace_back(n + j, n + 10);
  for (int i = 0; i < n + 10; i++)
    e.emplace_back(i, n + 11);

  InitG(n + 12, static_cast<int>(e.size()));
  for (std::size_t i = 0; i < e.size(); i++)
    MakeG(static_cast<int>(i), e[i].first, e[i].second);
}

void Bob(int n, int m, int u[], int v[])
{
  std::vector<std::vector<int>> e(n);
  for (int i = 0; i < m; i++)
  {
    e[u[i]].push_back(v[i]);
    e[v[i]].push_back(u[i]);
  }

  std::vector<std::vector<bool>> eb(n, std::vector<bool>(n, false));
  for (int i = 0; i < m; i++)
  {
    eb[u[i]][v[i]] = true;
    eb[v[i]][u[i]] = true;
  }

  int v_max = static_cast<int>(std::distance(
      e.begin(), std::max_element(e.begin(), e.end(), [](auto x, auto y) {
        return x.size() < y.size();
      })));
  int v_key = [&] {
    int res = 0;
    for (int i = 0; i < n; i++)
      if (i != v_max)
        res ^= i;
    for (int v : e[v_max])
      res ^= v;
    return res;
  }();
  auto v_ls = e[v_key];
  std::sort(v_ls.begin(), v_ls.end());
  do
  {
    bool valid = [&] {
      if (!eb[v_ls[1]][v_ls[3]])
        return false;
      for (int i = 0; i + 1 < 10; i++)
        if (!eb[v_ls[i]][v_ls[i + 1]])
          return false;
      return true;
    }();
    if (valid)
      break;
  } while (std::next_permutation(v_ls.begin(), v_ls.end()));

  auto is_normal = [&](int u) {
    return u != v_max && u != v_key &&
           std::find(v_ls.begin(), v_ls.end(), u) == v_ls.end();
  };

  std::vector<int> decode(n, -1);
  for (int i = 0; i < n; i++)
    if (is_normal(i))
    {
      decode[i] = 0;
      for (int j = 0; j < 10; j++)
        if (eb[i][v_ls[j]])
          decode[i] |= (1 << j);
    }

  std::vector<std::pair<int, int>> es;
  for (int i = 0; i < m; i++)
    if (decode[u[i]] != -1 && decode[v[i]] != -1)
      es.emplace_back(decode[u[i]], decode[v[i]]);

  InitMap(n - 12, static_cast<int>(es.size()));
  for (const auto &[u, v] : es)
    MakeMap(u, v);
}
