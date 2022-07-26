#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
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
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();
    int m = sc.next_int();
    int k = sc.next_int();

    std::vector<int> as(k);
    for (int &x: as)
      x = sc.next_int();

    auto valid = [&](int n, int m) {
      int64_t r  = 0;
      int     rm = 0;
      for (int x: as)
        if (x >= n * 2)
        {
          r += x / n;
          cm::check_max(rm, x / n);
        }
      if (rm == 2)
        return r >= m && (r - m) % 2 == 0;
      else
        return r >= m;
    };

    bool ans = valid(n, m) || valid(m, n);
    puts(ans ? "Yes" : "No");
  }
  return 0;
}
