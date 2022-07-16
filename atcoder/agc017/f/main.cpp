#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
#include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <cstdint>
#include <numeric>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int() - 1;
  int m = sc.next_int();

  auto constraints = [&] {
    int k = sc.next_int();

    struct constraint_t
    {
      uint32_t mask;
      uint32_t val;
    };

    std::vector<constraint_t> a(m);
    for (int i = 0; i < k; i++)
    {
      int x = sc.next_int() - 1;
      int p = sc.next_int() - 1;
      int v = sc.next_int();

      a[x].mask |= (1 << p);
      a[x].val |= (v << p);
    }

    return a;
  }();

  constexpr int MOD = 1'000'000'007;
  using int_t       = cm::intm<MOD>;

  auto partial_sum = [&](std::vector<int_t> a) {
    for (int i = 0; i < n; i++)
      for (uint32_t j = 0; j < (1u << n); j++)
        if (!(j & (1 << i)) && a[j])
        {
          auto vj = [&] {
            uint32_t pl = j & ((1 << i) - 1);
            uint32_t pj = j >> (i + 1);
            if (pj != 0)
              pj ^= (1 << __builtin_ctz(pj));
            return (pj << (i + 1)) | (1u << i) | pl;
          }();
          a[vj] += a[j];
        }
    return a;
  };

  std::vector<int_t> dp(1 << n, 0);
  dp[0] = 1;
  for (const auto &c: constraints)
  {
    dp = partial_sum(dp);
    for (uint32_t i = 0; i < (1u << n); i++)
      if ((i & c.mask) != c.val)
        dp[i] = 0;
    // see(c.mask, c.val, dp);
  }

  int_t ans = std::accumulate(dp.begin(), dp.end(), int_t(0));
  std::cout << ans << std::endl;

  return 0;
}
