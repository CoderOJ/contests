#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <cstdio>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  auto cs = [&] {
    std::vector<std::pair<int, int>> a;

    for (int i = 0; i < (1 << 14); i++)
      if (__builtin_popcount(i) == 7)
        a.emplace_back(i, ((1 << 14) - 1) ^ i);

    return a;
  }();

  int n = sc.next_int();

  for (int i = 1; i < n; i++)
  {
    for (int j = 0; j < i; j++)
      putchar(
          'a'
          + __builtin_ctz(
              (sc.next_char() == '1') ? (cs[i].first & cs[j].second)
                                      : (cs[i].second & cs[j].first)));
    puts("");
  }

  return 0;
}
