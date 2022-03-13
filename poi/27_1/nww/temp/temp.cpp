#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cmath>
#include <map>
#include <numeric>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

using i128_t = long long;

std::map<i128_t, std::pair<int, int>> pre;

constexpr int    P = 200000;
constexpr i128_t L = 1e18;

i128_t gcd(i128_t a, i128_t b)
{
  return b == 0 ? a : gcd(b, a % b);
}

i128_t lcm(i128_t a, i128_t b)
{
  a = a / gcd(a, b);
  if (b > L / a)
    return L + 1;
  else
    return a * b;
}

int main()
{
  for (int i = 1; i <= P; i++)
  {
    i128_t l = 1;
    for (int j = i;; j++)
    {
      l = lcm(l, j);
      if (l > L)
        break;
      if (j != i)
        pre.insert({l, {i, j}});
    }
  }

  int T = sc.next_int();
  for (int i = 0; i < T; i++)
  {
    i128_t n = sc.next_long();

    auto pre_it = pre.find(n);
    if (pre_it != pre.end())
    {
      std::cout << pre_it->second.first << " " << pre_it->second.second
                << std::endl;
    }
    else
    {
      std::pair<int, int> ans{-1, -1};

      {
        int al =
            std::max(1, static_cast<int>(std::pow((double)n, 1.0 / 2) - 5));
        int ar = al + 5;
        for (int i = al; i <= ar; i++)
          if (lcm(i, i + 1) == n)
            ans = {i, i + 1};
      }
      {
        int al =
            std::max(1, static_cast<int>(std::pow((double)n, 1.0 / 3) - 5));
        int ar = al + 5;
        for (int i = al; i <= ar; i++)
          if (lcm(i, lcm(i + 1, i + 2)) == n)
            ans = {i, i + 2};
      }
      {
        int al =
            std::max(1, static_cast<int>(std::pow((double)n * 2, 1.0 / 3) - 5));
        int ar = al + 5;
        for (int i = al; i <= ar; i++)
          if (lcm(i, lcm(i + 1, i + 2)) == n)
            ans = {i, i + 2};
      }

      if (ans.first != -1)
        std::cout << ans.first << " " << ans.second << std::endl;
      else
        puts("NIE");
    }
  }

  return 0;
}
