#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
using int_t = cm::intm<MOD>;

int main()
{
  int n = sc.next_int();
  int_t a = 0, b = 1;
  for (int i = 2; i <= n; i++)
    std::tie(a, b) = std::make_pair(b, (a + b) * i);
  std::cout << a << std::endl;
  return 0;
}
