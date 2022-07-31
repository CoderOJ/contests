#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
#include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  constexpr int MOD = 998'244'353;
  using int_t       = cm::intm<MOD>;
  using mu          = cm::math_util<int_t>;

  int n = sc.next_int();

  int_t cat = mu::binom.get(n * 2, n) - mu::binom.get(n * 2, n - 1);
  std::cout << cat * mu::fac.get(n) * int_t(2).pow(n) << std::endl;

  return 0;
}
