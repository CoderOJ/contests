#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
using int_t = cm::intm<MOD>;

int main()
{
  long long n = sc.next_long();
  int_t ans = 0;
  for (long long l = 1, r; l <= n; l = r + 1)
  {
    r = n / (n / l);
    if ((l + r) % 2 == 0)
      ans += int_t((l + r) / 2) * int_t(r - l + 1) * int_t(n / l);
    else
      ans += int_t(l + r) * int_t((r - l + 1) / 2) * int_t(n / l);
  }
  std::cout << ans << std::endl;
  return 0;
}

