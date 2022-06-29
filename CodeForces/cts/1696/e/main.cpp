#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
#include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
using int_t       = cm::intm<MOD>;
using mu          = cm::math_util<int_t>;

int main()
{
  mu::binom.require(1'000'000);

  int n = sc.next_int() + 1;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  if (a[0] == 0)
  {
    puts("0");
    return 0;
  }

  n += 1;
  a.push_back(0);

  auto test = [&](int x, int y) {
    if (x < 0 || y < 0)
      return false;
    else
      return y < a[x];
  };

  int_t ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = a[i];; j++)
    {
      bool flag = false;
      if (test(i, j - 1))
      {
        ans += mu::binom(i + j - 1, i);
        flag = true;
      }
      if (test(i - 1, j))
      {
        ans += mu::binom(i + j - 1, i - 1);
        flag = true;
      }
      if (!flag)
        break;
    }

  std::cout << ans - 1 << std::endl;

  return 0;
}
