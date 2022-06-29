#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();

    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int();

    if (std::all_of(a.begin(), a.end(), [](int x) { return x == 0; }))
    {
      puts("0");
    }
    else
    {
      int zl = -1;
      int zr = -1;
      int zc = 0;
      for (int i = 0; i < n; i++)
        if (a[i] != 0)
        {
          if (zl == -1)
            zl = i;
          zr = i;
          zc += 1;
        }

      if (zr - zl + 1 == zc)
        puts("1");
      else
        puts("2");
    }
  }
  return 0;
}
