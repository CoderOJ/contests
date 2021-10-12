#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#include <limits>
#include <cmath>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();
    int m = sc.next_int();

    auto calc = [&](int x, int y)
    {
      if (x < 0 || x > n || y < 0 || y > m)
        return std::numeric_limits<double>::max();
      if (std::__gcd(x, y) != 1)
        return std::numeric_limits<double>::max();
      if (std::__gcd(n - x, m - y) != 1)
        return std::numeric_limits<double>::max();
      if (1ll * x * m == 1ll * y * n)
        return std::numeric_limits<double>::max();
      return std::sqrt(1ll * x * x + 1ll * y * y) + 
             std::sqrt(1ll * (n-x) * (n-x) + 1ll * (m-y) * (m-y));
    };

    if (std::__gcd(n, m) == 1)
    {
      printf("%.12lf\n", std::sqrt(1ll * n * n + 1ll * m * m));
    }
    else
    {
      double ans = std::numeric_limits<double>::max();
      for (int x = 0; x < n; x++)
      {
        int y = 1ll * x * m / n;
        check_min(ans, calc(x, y - 1));
        check_min(ans, calc(x, y + 0));
        check_min(ans, calc(x, y + 1));
      }
      
      printf("%.12lf\n", ans);
    }
  }
  return 0;
}

