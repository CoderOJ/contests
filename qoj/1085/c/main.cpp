#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
#include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  constexpr int MOD = 998'244'353;
  using int_t       = cm::intm<MOD>;

  int n = sc.next_int();

  std::vector<int_t> a(n + 1);
  std::vector<int_t> pa(n + 2);
  a[0]  = 1;
  a[1]  = 1;
  pa[0] = 0;
  pa[1] = 1;
  pa[2] = 2;

  for (int i = 2; i <= n; i++)
  {
    a[i] = pa[i];

    int pw = 31 - __builtin_clz(i);
    for (int j = pw - 1; j >= 0; j--)
      if (i & (1 << j))
        a[i] -= pa[1 << (j + 1)] - pa[1 << j];

    pa[i + 1] = pa[i] + a[i];
  }

  std::cout << pa[n + 1] - 1 << std::endl;

  return 0;
}
