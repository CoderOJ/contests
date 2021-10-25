#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#include <numeric>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
#define int long long

  int n = sc.next_int();
  std::vector<int> a(n), p(n + 1);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  std::partial_sum(a.begin(), a.end(), p.begin() + 1);

  std::vector<std::vector<int>> dp(n, std::vector<int>(n + 1, -0x3f3f3f3f));
  for (int i = 0; i < n; i++) dp[i][i] = 0;
  for (int i = n - 2; i >= 0; i--)
    for (int j = i + 1; j <= n; j++)
    {
      dp[i][j] = std::max({
        a[i] + p[j] - p[i + 1] - dp[i + 1][j],
        a[j - 1] + p[j - 1] - p[i] - dp[i][j - 1]
      });
      see(p[i], p[i + 1], p[j], p[j - 1]);
      see(i, j, dp[i][j]);
    }

  std::cout << dp[0][n] << std::endl;

  return 0;
}

