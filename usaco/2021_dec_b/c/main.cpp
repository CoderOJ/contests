#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstring>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 55;
char          map[N][N];
long long     dp[N][N][5][2];

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();
    int k = sc.next_int();
    for (int i = 0; i < n; i++)
      sc.next_token(map[i]);

    memset(dp, 0, sizeof(dp));
    dp[0][1][0][0] = 1;
    dp[1][0][0][1] = 1;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (map[i][j] == '.')
          for (int k = 0; k <= 3; k++)
          {
            if (j + 1 < n)
            {
              dp[i][j + 1][k][0] += dp[i][j][k][0];
              dp[i][j + 1][k + 1][0] += dp[i][j][k][1];
            }
            if (i + 1 < n)
            {
              dp[i + 1][j][k][1] += dp[i][j][k][1];
              dp[i + 1][j][k + 1][1] += dp[i][j][k][0];
            }
          }

    long long ans = 0;
    for (int i = 0; i <= k; i++)
      ans += dp[n - 1][n - 1][i][0] + dp[n - 1][n - 1][i][1];
    std::cout << ans << std::endl;
  }
  return 0;
}
