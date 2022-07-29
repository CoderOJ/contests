#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
#include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <numeric>
#include <ostream>
#include <utility>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  constexpr int MOD = 998244353;
  using int_t       = cm::intm<MOD>;

  int n = sc.next_int();

  std::vector<int> c(6l * n);
  for (int i = 0; i < 3 * n; i++)
    c[i] = sc.next_int() - 1;
  std::copy(c.begin(), c.begin() + 3l * n, c.begin() + 3l * n);

  auto pos0 = [&]() {
    std::vector a{c.begin()};
    for (auto i = std::next(c.begin()); i != c.end(); i++)
      if (*i == *c.begin())
        a.emplace_back(i);
    return a;
  }();

  auto solve = [n](auto l, auto r) -> int_t {
    int m = (int)std::distance(l, r);

    std::vector<std::vector<int>> occur(n);
    for (int i = 0; i < m; i++)
      occur[*std::next(l, i)].push_back(i);

    std::vector<std::pair<int, int>> inters;
    for (const auto &v: occur)
      for (size_t i = 0; i + 1 < v.size(); i++)
        inters.emplace_back(v[i], v[i + 1]);

    struct dp_t
    {
      int   max = 0;
      int_t cnt = 0;

      dp_t(int max = 0, int_t cnt = 0) : max(max), cnt(cnt) {}

      dp_t(const dp_t &lhs, const dp_t &rhs) :
          max(std::max(lhs.max, rhs.max)),
          cnt((lhs.max == max ? lhs.cnt : 0) + (rhs.max == max ? rhs.cnt : 0))
      {
      }

      dp_t shift(int det) const
      {
        return {max + det, cnt};
      }
    };

    std::sort(inters.begin(), inters.end(), [](auto x, auto y) {
      return x.second < y.second;
    });

    std::vector<dp_t> dp(m + 1);
    dp[0] = {0, 1};

    auto it = inters.begin();
    for (int ir = 1; ir <= m; ir++)
    {
      dp[ir] = dp[ir - 1];
      while (it != inters.end() && it->second + 1 == ir)
      {
        dp[ir] = dp_t(dp[ir], dp[it->first].shift(1));
        it     = std::next(it);
      }
    }

    return (dp.back().max == n - 1) ? dp.back().cnt : 0;
  };

  auto ans = solve(pos0[1] + 1, pos0[3]) //
           + solve(pos0[2] + 1, pos0[4]) //
           + solve(pos0[3] + 1, pos0[5]);
  std::cout << ans << std::endl;

  return 0;
}
