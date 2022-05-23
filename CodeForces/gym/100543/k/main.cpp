#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <limits>
#include <numeric>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();
    int k = sc.next_int();

    std::vector<std::pair<int, int>> a(n);
    for (int i = 0; i < n; i++)
    {
      a[i].first  = sc.next_int();
      a[i].second = sc.next_int();
    }

    std::sort(a.begin(), a.end());
    std::reverse(a.begin(), a.end());

    std::vector<int> dp(k + 2, std::numeric_limits<int>::min() / 2);
    dp[0] = std::numeric_limits<int>::max() / 2;
    for (const auto &[x, y] : a)
    {
      for (int i = k; i >= 0; i--)
        check_max(dp[i + 1], std::min(dp[i], x) - y);
      see(dp);
    }

    std::cout << std::max(dp[k + 1], 0) << std::endl;
  }
  return 0;
}
