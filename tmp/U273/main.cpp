#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/math_util"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  using int_t = cm::intm<>;
  using mu    = cm::math_util<int_t>;

  int n = sc.next_int();
  int m = 0;
  for (int i = 0; i < n; i++)
    m += sc.next_int();

  std::cout << mu::fac.get(m) / (m - n + 1) << std::endl;

  return 0;
}
