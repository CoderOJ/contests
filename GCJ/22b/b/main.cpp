#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cmath>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

bool check_on(int64_t r, int64_t x)
{
  return round(sqrt(r * r - x * x)) == x;
}

int64_t calc(int64_t n)
{
  int64_t bx = static_cast<int64_t>(n / sqrt(2));
  int64_t res = (int64_t)(bx + 1) * 8 - 4;
  if (check_on(n, bx)) 
    res -= 4;
  if (check_on(n, bx + 1)) 
    res += 4;
  return res;
}

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    printf("Case #%d: ", i + 1);

    int64_t n = sc.next_int();

    int64_t ans0 = 0;
    for (int64_t i = -n; i <= n; i++)
    {
      int64_t c = int64_t(floor(sqrt((n + 0.5) * (n + 0.5) - i * i)));
      ans0 += c * 2 + 1;
    }

    int64_t ans1 = 1;
    for (int64_t i = 1; i <= n; i++)
      ans1 += calc(i);

    std::cout << ans0 - ans1 << std::endl;
  }
  return 0;
}
