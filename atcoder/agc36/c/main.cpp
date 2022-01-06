#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/math_util"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  constexpr int MOD = 998244353;
  using int_t       = cm::intm<MOD>;
  using mu          = cm::math_util<int_t>;

  int n = sc.next_int();
  int m = sc.next_int();

  int_t ans = 0;
  for (int i = m * 2; i <= m * 3; i += 2)
    ans += mu::binom.get(i / 2 + n - 1, n - 1) * mu::binom.get(n, m * 3 - i);
  for (int i = m * 2 + 1; i <= m * 3; i++)
    ans -= mu::binom.get(m * 3 - i + n - 2, n - 2) * n;

  std::cout << ans << std::endl;

  return 0;
}
