#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
#include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <cstdint>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();

  auto e = [&] {
    std::vector<uint32_t> a(n);
    for (int i = 0; i < m; i++)
    {
      int u = sc.next_int() - 1;
      int v = sc.next_int() - 1;
      a[u] |= (1u << v);
    }
    return a;
  }();

  constexpr int MOD = 1'000'000'007;
  using int_t       = cm::intm<MOD>;

  auto p2 = [&] {
    std::vector<int_t> a(n + 1);
    a[0] = 1;
    for (int i = 0; i + 1 <= n; i++)
      a[i + 1] = a[i] + a[i];
    return a;
  }();

  auto dp = [&] {
    auto same_01 = [&](uint32_t m) {
      return (m & 1) == ((m >> 1) & 1);
    };

    std::vector<int_t> a(1 << n);
    a[0] = 1;
    for (uint32_t s = 0; s < (1u << n); s++)
    {
      uint32_t rs = ((1u << n) - 1) ^ s;
      for (uint32_t t = s; t != 0; t = (t - 1) & s)
        if (same_01(t) && a[s ^ t])
        {
          auto r2t = [&] {
            int_t a = 1;
            for (int ru = 0; ru < n; ru++)
              if (rs & (1u << ru))
                a *= (p2[__builtin_popcount(e[ru] & t)] - 1);
            return a;
          }();

          auto t2r = [&] {
            int_t a = 1;
            for (int tu = 0; tu < n; tu++)
              if (t & (1u << tu))
                a *= p2[__builtin_popcount(e[tu] & rs)];
            return a;
          }();

          a[s] += a[s ^ t] * r2t * t2r;
        }
    }
    return a;
  }();

  std::cout << int_t(2).pow(m) - dp[(1u << n) - 1] << std::endl;

  return 0;
}
