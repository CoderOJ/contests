#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<std::vector<char>> mp(n, std::vector<char>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      mp[i][j] = sc.next_char();

  std::vector<std::vector<int>> dp(n, std::vector<int>(n));
  dp[0][0] = mp[0][0] == '.';
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (mp[i][j] == '.')
      {
        if (i) dp[i][j] = (dp[i][j] + dp[i - 1][j]) % 1'000'000'007;
        if (j) dp[i][j] = (dp[i][j] + dp[i][j - 1]) % 1'000'000'007;
      }

  printf("%d\n", dp[n - 1][n - 1]);
  return 0;
}
