#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int(), m = sc.next_int();
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0x3f3f3f3f));
  for (int i = 1; i <= n && i <= m; i++) dp[i][i] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
    {
      for (int k = 1; k < i; k++)
        check_min(dp[i][j], dp[k][j] + dp[i - k][j]);
      for (int k = 1; k < j; k++)
        check_min(dp[i][j], dp[i][k] + dp[i][j - k]);
    }
  std::cout << dp[n][m] - 1 << std::endl;
  return 0;
}

