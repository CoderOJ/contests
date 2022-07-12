#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <queue>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();

  auto read_tree = [&] {
    std::vector<std::vector<int>> e(n);
    for (int i = 0; i < n - 1; i++)
    {
      int u = sc.next_int() - 1;
      int v = sc.next_int() - 1;
      e[u].push_back(v);
      e[v].push_back(u);
    }
    return e;
  };

  auto e0 = read_tree();
  auto e1 = read_tree();

  std::map<std::pair<int, int>, uint8_t> m_dup;
  std::queue<std::pair<int, int>>        q_dup;

  auto insert_edge = [&](int u, int v, uint8_t m) {
    auto  uv = std::minmax(u, v);
    auto &p  = m_dup[uv];
    p |= m;
    if (p == 0b11)
      q_dup.emplace(uv);
  };

  for (int u = 0; u < n; u++)
    for (int v: e0[u])
      if (u < v)
        insert_edge(u, v, 0b01);
  for (int u = 0; u < n; u++)
    for (int v: e1[u])
      if (u < v)
        insert_edge(u, v, 0b10);

  std::vector<int> p(n);
  for (int i = 0; i < n; i++)
    p[i] = i;
  auto get = cm::y_combinate([&](auto &&f, int u) -> int {
    return u == p[u] ? u : p[u] = f(p[u]);
  });

  int join_cnt = 0;
  while (!q_dup.empty())
  {
    auto [u, v] = q_dup.front();
    q_dup.pop();

    u = get(u);
    v = get(v);

    if (u != v)
    {
      {
        auto cu = e0[u].size() + e1[u].size();
        auto cv = e0[v].size() + e1[v].size();
        if (cv > cu)
          std::swap(u, v);
      }

      // see(u, v);

      join_cnt += 1;

      for (int vv: e0[v])
      {
        vv = get(vv);
        if (vv != u && vv != v)
        {
          e0[u].push_back(vv);
          e0[vv].push_back(u);
          insert_edge(u, vv, 0b01);
        }
      }
      for (int vv: e1[v])
      {
        vv = get(vv);
        if (vv != u && vv != v)
        {
          e1[u].push_back(vv);
          e1[vv].push_back(u);
          insert_edge(u, vv, 0b10);
        }
      }

      p[v] = u;
    }
  }

  if (join_cnt == n - 1)
    puts("YES");
  else
    puts("NO");

  return 0;
}
