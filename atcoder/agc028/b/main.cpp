#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#include <numeric>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  using int_t = cm::intm<1'000'000'007>;

  int n = sc.next_int();
  std::vector<int_t> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  std::vector<int_t> par_inv(n + 1);
  for (int i = 1; i <= n; i++)
    par_inv[i] = int_t(1) / i;
  std::partial_sum(par_inv.begin(), par_inv.end(), par_inv.begin());

  int_t ans = 0;
  for (int i = 0; i < n; i++)
    ans += a[i] * (par_inv[i + 1] + par_inv[n - i] - 1);

  for (int i = 1; i <= n; i++)
    ans *= i;

  std::cout << ans << std::endl;

  return 0;
}

