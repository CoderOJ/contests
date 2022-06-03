#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/math_util"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
using int_t       = cm::intm<MOD>;
using mu          = cm::math_util<int_t>;

int main()
{
  int n = sc.next_int();
  int m = sc.next_int() - 1;

  int_t ans = 0;
  for (int k = 0; k <= m; k++)
    ans += mu::binom.get(n + 1, k) * int_t(m + 1 - k).pow(n) * int_t(-1).pow(k);
  std::cout << ans << std::endl;

  return 0;
}
