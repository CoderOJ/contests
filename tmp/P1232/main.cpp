#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <iterator>
#include <tuple>
#include <utility>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

double solve(const std::vector<std::pair<int, int>> &dfns, auto begin, auto end)
{
  if (begin == end)
    return 0;
  else if (std::next(begin) == end)
    return 1;
  else
  {
    if (dfns.size() == 1)
    {
      int u  = *begin;
      int u1 = *std::next(begin);
      if (u1 == u + 1)
      {
        return 0.5
             + solve(
                   {{dfns[0].first + 1, dfns[0].second}},
                   std::next(begin),
                   end);
      }
      else
      {
        std::vector<int> rs;
        while (*begin != u + 1)
        {
          rs.push_back(*begin);
          begin = std::next(begin);
        }
        rs.push_back(dfns[0].second);

        std::vector<std::pair<int, int>> v_dfns;
        for (int i = 0; i + 1 < (int)rs.size(); i++)
          if (rs[i] + 1 != rs[i + 1])
            v_dfns.emplace_back(rs[i] + 1, rs[i + 1]);

        return 1 + solve(v_dfns, begin, end);
      }
    }
    else
    {
      std::vector<std::pair<int, int>> v_dfns;

      auto shift_interval = [&](int cl, int cr) {
        std::vector<int> rs;
        while (begin != end && cl <= *begin && *begin < cr)
        {
          rs.push_back(*begin);
          begin = std::next(begin);
        }
        rs.push_back(cr);

        for (int i = 0; i + 1 < (int)rs.size(); i++)
          if (rs[i] + 1 != rs[i + 1])
            v_dfns.emplace_back(rs[i] + 1, rs[i + 1]);
      };

      for (size_t i = 0; i < dfns.size() - 1; i++)
        std::apply(shift_interval, dfns[i]);

      if (v_dfns.empty())
      {
        return solve({dfns.back()}, begin, end);
      }
      else
      {
        std::apply(shift_interval, dfns.back());
        return 1 + solve(v_dfns, begin, end);
      }
    }
  }
}

int main()
{
  int n = sc.next_int();

  auto dfn = [&] {
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
      int u = sc.next_int() - 1;
      a[u]  = i;
    }
    return a;
  }();

  auto bfs_order = [&] {
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
      int u = sc.next_int() - 1;
      a[i]  = dfn[u];
    }
    return a;
  }();

  auto ans = solve({{1, n}}, bfs_order.begin() + 1, bfs_order.end()) + 1;
  printf("%.3f\n", ans);

  return 0;
}
