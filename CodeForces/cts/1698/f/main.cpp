#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <cstddef>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();

    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int();
    for (int i = 0; i < n; i++)
      b[i] = sc.next_int();

    bool valid = [&] {
      if (a.front() != b.front())
        return false;
      if (a.back() != b.back())
        return false;

      auto get_pset = [&](const std::vector<int> &a) {
        std::vector<std::pair<int, int>> res;
        for (size_t i = 0; i + 1 < a.size(); i++)
        {
          const auto &[x, y] = std::minmax(a[i], a[i + 1]);
          res.emplace_back(x, y);
        }
        std::sort(res.begin(), res.end());
        return res;
      };

      if (get_pset(a) != get_pset(b))
        return false;

      return true;
    }();

    if (!valid)
    {
      puts("NO");
    }
    else
    {
      puts("YES");

      std::vector<std::pair<size_t, size_t>> ops;
      cm::y_combinate(
          [&](auto &&self, std::vector<int> a, std::vector<int> b) -> void {
            if (a.size() > 2)
            {
              int a0 = *std::prev(a.end(), 1);
              int a1 = *std::prev(a.end(), 2);
              int b1 = *std::prev(b.end(), 2);

              if (a1 == b1)
              {
                a.pop_back();
                b.pop_back();
                self(a, b);
              }
              else
              {
                // see(a);
                // see(b);

                auto p = [&]() -> ptrdiff_t {
                  for (ptrdiff_t i = (ptrdiff_t)a.size() - 2; i - 1 >= 0; i--)
                    if (a[i] == b1 && a[i - 1] == a0)
                      return i;
                  for (ptrdiff_t i = (ptrdiff_t)a.size() - 2; i - 1 >= 0; i--)
                    if (a[i] == a0 && a[i - 1] == b1)
                      return i;
                  return 0;
                }();
                // see(p);
                cm_assert(p != 0);

                if (a[p] == b1 && a[p - 1] == a0)
                {
                  ops.emplace_back(p - 1, a.size() - 1);
                  std::reverse(a.begin() + (p - 1), a.end());

                  a.pop_back();
                  b.pop_back();
                  self(a, b);
                }
                else
                {
                  auto [ql, qr] = [&]() -> std::pair<ptrdiff_t, ptrdiff_t> {
                    for (ptrdiff_t ql = 0; ql < p; ql++)
                      for (ptrdiff_t qr = p + 1; qr < (ptrdiff_t)a.size(); qr++)
                        if (a[ql] == a[qr])
                          return {ql, qr};
                    return {-1, -1};
                  }();
                  // see(ql, qr);

                  ops.emplace_back(ql, qr);
                  std::reverse(a.begin() + ql, a.begin() + qr + 1);
                  self(a, b);
                }
              }
            }
          })(a, b);

      std::cout << ops.size() << std::endl;
      for (const auto &[x, y]: ops)
        std::cout << x + 1 << " " << y + 1 << std::endl;
    }
  }

  return 0;
}
