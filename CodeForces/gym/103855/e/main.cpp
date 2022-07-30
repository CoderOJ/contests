#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <cstdio>
#include <list>
#include <utility>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int t = sc.next_int();

  auto as = [&] {
    struct segment_t
    {
      std::vector<int> p;
      uint32_t         c_mask;
    };

    static int cmap[26];
    cmap['R' - 'A'] = 0;
    cmap['S' - 'A'] = 1;
    cmap['P' - 'A'] = 2;

    std::vector<segment_t> a;
    for (int i = 0; i < n; i++)
    {
      int c = cmap[sc.next_char() - 'A'];
      if (a.empty() || (a.back().c_mask | (1 << c)) == 7)
        a.push_back({});
      a.back().p.push_back(c);
      a.back().c_mask |= (1 << c);
    }

    return a;
  }();

  auto play = [t](const auto &s) {
    if (__builtin_popcount(s.c_mask) == 1)
      return s.p;
    else
    {
      int va = __builtin_ctz(s.c_mask);
      int vb = __builtin_ctz(s.c_mask ^ (1 << va));
      if ((vb + 1) % 3 == va)
        std::swap(va, vb);

      int n = (int)s.p.size();

      std::vector<int> res(n, va);
      for (int i = 0, vb_cnt = 0; i < n; i++)
        if (s.p[i] == vb)
        {
          res[std::max(vb_cnt, i - t)] = vb;
          vb_cnt++;
        }

      return res;
    }
  };

  auto dump = [](const auto &s) {
    static char cmap[] = "RSP";
    for (int c: s)
      putchar(cmap[c]);
    return 0;
  };

  cm::transfer(
      as,               //
      cm::mapper(play), //
      cm::mapper(dump));

  return 0;
}
