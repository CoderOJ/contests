#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();
    int k = sc.next_int();

    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int();

    int m = sc.next_int();

    std::vector<int> b(m);
    for (int i = 0; i < m; i++)
      b[i] = sc.next_int();

    auto parse = [](const std::vector<int> &a, int k) {
      std::vector<std::pair<int, int64_t>> res;
      for (int x : a)
      {
        int xv = x;
        int xc = 1;
        while (xv % k == 0)
        {
          xv /= k;
          xc *= k;
        }
        if (!res.empty() && res.back().first == xv)
          res.back().second += xc;
        else
          res.emplace_back(xv, xc);
      }
      return res;
    };

    puts(parse(a, k) == parse(b, k) ? "Yes" : "No");
  }
  return 0;
}
