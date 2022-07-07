#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();

  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  std::sort(a.begin(), a.end());

  std::vector<std::vector<int>> e(n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (i != j && std::gcd(a[i], a[j]) != 1)
      {
        see(i, j);
        e[i].push_back(j);
      }

  auto join_us = [&](const std::vector<std::vector<int>> &us) {
    std::priority_queue<std::tuple<int, size_t, size_t>> que;

    for (size_t i = 0; i < us.size(); i++)
      if (!us[i].empty())
        que.emplace(us[i][0], i, 0);

    std::vector<int> res;
    while (!que.empty())
    {
      const auto [v, i, j] = que.top();
      que.pop();
      res.push_back(v);
      if (j + 1 < us[i].size())
        que.emplace(us[i][j + 1], i, j + 1);
    }

    return res;
  };

  std::vector<int> vis(n, false);

  std::vector<std::vector<int>> us;
  for (int u = 0; u < n; u++)
    if (!vis[u])
    {
      auto cur_u = cm::y_combinate([&](auto &&self, int u) -> std::vector<int> {
        vis[u] = true;

        std::vector<std::vector<int>> us;
        for (int v: e[u])
          if (!vis[v])
            us.emplace_back(self(v));

        auto res = join_us(us);
        res.insert(res.begin(), u);
        return res;
      })(u);
      us.emplace_back(cur_u);
    }

  auto ans = join_us(us);
  for (int u: ans)
    std::cout << a[u] << " ";
  std::cout << std::endl;

  return 0;
}
