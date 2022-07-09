#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <limits>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();

  std::vector<std::vector<std::pair<int, int>>> e(n);

  for (int i = 0; i < n - 1; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    int w = sc.next_int();

    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
  }

  int64_t ew_sum   = 0;
  int     ew_extra = std::numeric_limits<int>::max();
  cm::y_combinate([&](auto &&self, int u, int f) -> int {
    int size       = 1;
    int v_size_max = 0;
    for (const auto &[v, w]: e[u])
      if (v != f)
      {
        int v_size = self(v, u);

        size += v_size;
        cm::check_max(v_size_max, v_size);

        ew_sum += static_cast<int64_t>(std::min(v_size, n - v_size)) * 2 * w;
        if (v_size * 2 == n)
          ew_extra = w;
      }

    if (v_size_max * 2 < n && (n - size) * 2 < n)
    {
      for (const auto &[v, w]: e[u])
        cm::check_min(ew_extra, w);
    }
    return size;
  })(0, 0);

  std::cout << ew_sum - ew_extra << std::endl;

  return 0;
}
