#include "/home/jack/cm/debug"
#include "/home/jack/cm/util"
#import "chameleon.h"
#include <algorithm>
#include <string>

int query_dup(const std::basic_string<int> &a)
{
  if (a.size() <= 1)
    return 0;
  std::vector<int> v;
  v.reserve(a.size());
  for (int x : a)
    v.push_back(x + 1);
  return static_cast<int>(a.size()) - Query(v);
}

void Solve(int n)
{
  std::vector<std::vector<int>> e(n * 2);

  auto get_color = [&](const std::vector<int> &us) {
    std::vector<bool> in_set(n * 2, false);
    for (int u : us)
      in_set[u] = true;

    std::basic_string<int>  s[2];
    std::basic_string<bool> vis(n * 2, false);

    auto dfs = cm::y_combinate([&](const auto &f, int u, int c) -> void {
      vis[u] = true;
      s[c].push_back(u);
      for (int v : e[u])
        if (in_set[v] && !vis[v])
          f(v, 1 - c);
    });

    for (int u : us)
      if (!vis[u])
        dfs(u, 0);

    return std::make_pair(std::move(s[0]), std::move(s[1]));
  };

  std::vector<int> match(n * 2, -1);

  for (int i = 0; i < n * 2; i++)
    while (e[i].size() < 3)
    {
      std::vector<int> us;
      for (int u = 0; u < i; u++)
        if (u != i && std::find(e[i].begin(), e[i].end(), u) == e[i].end())
          us.push_back(u);

      const auto &[s0, s1] = get_color(us);
      see(s0, s1, i);

      auto solve = cm::y_combinate(
          [&](const auto &f, const std::basic_string<int> &s) -> void {
            if (s.size() == 1)
            {
              see("add_edge", i, s[0]);
              e[i].push_back(s[0]);
              e[s[0]].push_back(i);
            }
            else
            {
              size_t m = s.size() / 2;
              if (query_dup(s.substr(0, m) + i))
                f(s.substr(0, m));
              else
                f(s.substr(m));
            }
          });

      if (query_dup(s0 + i))
        solve(s0);
      else if (query_dup(s1 + i))
        solve(s1);
      else
        break;
    }

  for (int i = 0; i < n * 2; i++)
    if (e[i].size() == 3)
    {
      if (query_dup({i, e[i][0], e[i][1]}) == 2)
        match[i] = e[i][2];
      else if (query_dup({i, e[i][0], e[i][2]}) == 2)
        match[i] = e[i][1];
      else if (query_dup({i, e[i][1], e[i][2]}) == 2)
        match[i] = e[i][0];
      else
        abort();
      see(i, match[i]);
    }

  for (int u = 0; u < n * 2; u++)
    for (int v : e[u])
      if (match[u] != v && match[v] != u)
        if (u < v)
        {
          see(u, v);
          Answer(u + 1, v + 1);
        }
}
