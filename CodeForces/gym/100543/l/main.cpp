#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <limits>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();

    std::vector<int> vals;

    std::vector<std::tuple<int, int, int>> a;
    for (int i = 0; i < n; i++)
    {
      int l = sc.next_int() - 1;
      int r = sc.next_int();
      int v = sc.next_int();
      a.emplace_back(v, l, r);
      vals.push_back(l);
      vals.push_back(r);
    }

    std::sort(vals.begin(), vals.end());
    vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
    for (auto &[v, l, r] : a)
    {
      l = static_cast<int>(std::distance(
          vals.begin(), std::lower_bound(vals.begin(), vals.end(), l)));
      r = static_cast<int>(std::distance(
          vals.begin(), std::lower_bound(vals.begin(), vals.end(), r)));
    }

    int m = static_cast<int>(vals.size());

    std::vector<std::vector<int>> dp(m, std::vector<int>(m + 1));
    for (int i = m - 1; i >= 0; i--)
    {
      std::fill(dp[i].begin(), dp[i].begin() + i + 1, 0);
      for (int j = i + 1; j <= m; j++)
      {
        std::tuple<int, int, int> max_inter{0, 0, 0};
        for (const auto &[v, l, r] : a)
          if (l >= i && r <= j)
            check_max(max_inter, std::make_tuple(v, l, r));
        const auto [mv, ml, mr] = max_inter;
        if (mv == 0)
          dp[i][j] = 0;
        else
        {
          dp[i][j] = std::numeric_limits<int>::max();
          for (int k = ml; k < mr; k++)
            check_min(dp[i][j], mv + dp[i][k] + dp[k + 1][j]);
        }
      }
    }

    std::cout << dp[0][m] << std::endl;
  }
  return 0;
}
