#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <limits>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();

  using dp_t = std::array<int64_t, 3>;

  int64_t c = sc.next_int();

  std::array<dp_t, 3> dp;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
    {
      if (i == j)
        dp[i][j] = c * i;
      else
        dp[i][j] = std::numeric_limits<int64_t>::max() / 2;
    }

  auto trans = [&](const dp_t &a, int64_t c) -> dp_t {
    return {
        std::min({a[2]}),
        std::min({a[1], a[2]}) + c,
        std::min({a[0], a[1], a[2]}) + c * 2,
    };
  };

  auto dp_trans = [&](std::array<dp_t, 3> a, int64_t c) {
    for (int i = 0; i < 3; i++)
      a[i] = trans(a[i], c);
    return a;
  };

  dp = dp_trans(dp, sc.next_int());

  for (int i = 0; i < n - 2; i++)
  {
    dp = dp_trans(dp, sc.next_int());
    see(dp);

    int64_t ans = std::numeric_limits<int64_t>::max();
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        if (i + j >= 2)
          cm::check_min(ans, dp[i][j]);
    printf("%.6f ", (double)ans / 2);
  }

  std::cout << std::endl;

  return 0;
}
