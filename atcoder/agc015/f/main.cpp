#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
#include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <cstdint>
#include <iterator>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  constexpr int MOD = 1'000'000'007;
  using int_t       = cm::intm<MOD>;

  auto fib = [&] {
    std::vector<int64_t> a{0, 1};
    while (a.back() <= 2'000'000'000'000'000'000)
      a.push_back(*std::prev(a.end(), 2) + *std::prev(a.end(), 1));
    return a;
  }();

  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int64_t x = sc.next_long();
    int64_t y = sc.next_long();
    if (x > y)
      std::swap(x, y);

    auto ans_max = [&] {
      for (int i = 0;; i++)
        if (fib[i] > x || fib[i + 1] > y)
          return i - 1;
    }();

    if (x == 1)
    {
      std::cout << 1 << " " << int_t(y) << std::endl;
    }
    else if (x == 2 && y == 2)
    {
      std::cout << 1 << " " << 4 << std::endl;
    }
    else
    {
      auto ans_cnt = cm::y_combinate(
          [&](auto &&self, int64_t cx, int64_t cy, int d) -> int_t {
            int64_t nx = cx * fib[d - 1] + cy * fib[d];
            int64_t ny = cx * fib[d] + cy * fib[d + 1];
            if (nx > x || ny > y)
              return 0;
            else if (d == 1)
            {
              return (y - cx) / cy + (x >= cx + cy ? (x - cx) / cy : 0);
            }
            else
            {
              int_t res = 0;
              for (int64_t cz = cx + cy;; cz += cy)
              {
                int_t cur = self(cy, cz, d - 1);
                res += cur;
                if (cur == 0)
                  break;
              }
              return res;
            }
          })(0, 1, ans_max);

      std::cout << ans_max - 1 << " " << ans_cnt << std::endl;
    }
  }

  return 0;
}
