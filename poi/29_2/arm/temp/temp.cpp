#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cmath>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int64_t n, a, b;

__int128_t ans;

template <class int_t>
int_t pow(int_t a, int_t b)
{
  return b == 0 ? int_t(1) : pow(a, b - 1) * a;
}

int main()
{
  n = sc.next_long();
  a = sc.next_long();
  b = sc.next_long();

  ans = (__int128_t)(1) << 126;

  for (int i = 1; i <= 64; i++)
  {
    int64_t base = static_cast<int64_t>(std::pow(n, 1.0 / i));
    base         = std::max<int64_t>(base - 4, 2);
    while (pow<__int128_t>(base, i) <= n)
      base += 1;
    int k = 0;
    while (pow<__int128_t>(base, k) * pow<__int128_t>(base - 1, i - k) <= n)
      k += 1;
    check_min(ans, a * i + __int128_t(b) * ((base - 1) * k + (base - 2) * (i - k)));
  }

  std::cout << static_cast<int64_t>(ans) << std::endl;

  return 0;
}
