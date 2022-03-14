#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <complex>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 100003;
using int_t       = cm::intm<MOD>;

constexpr int N = 100005;

int n, k, c;
int a[N];

using equation_t = std::pair<int_t, int_t>;

equation_t p[N];

int main()
{
  n = sc.next_int();
  k = sc.next_int();
  for (int i = 1; i <= n; i++)
    a[i] = sc.next_int();

  for (int i = n; i >= 1; i--)
    if (a[i] == 1)
    {
      c += 1;
      for (int j = 1; j * j <= i; j++)
        if (i % j == 0)
        {
          a[j] ^= 1;
          if (j * j != i)
            a[i / j] ^= 1;
        }
    }

  see(c);

  for (int i = 0; i <= k; i++)
    p[i] = {i, 0};
  p[k + 1]    = {0, 1};
  int_t inv_n = int_t(n).inv();
  for (int i = k + 1; i < n; i++)
  {
    int_t pp     = i * inv_n;
    int_t qq     = (n - i) * inv_n;
    int_t qq_inv = qq.inv();
    p[i + 1]     = (p[i] - equation_t(1, 0) - equation_t(pp, pp) * p[i - 1]) *
               equation_t(qq_inv, qq_inv);
  }

  int_t x = (1 + p[n - 1].first - p[n].first) / (p[n].second - p[n - 1].second);

  int_t ans = p[c].first + p[c].second * x;
  for (int i = 1; i <= n; i++)
    ans *= i;
  std::cout << ans << std::endl;

  return 0;
}
