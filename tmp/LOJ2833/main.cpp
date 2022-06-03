#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
using int_t       = cm::intm<MOD>;

constexpr int N = 3005;

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();

  static int_t dp[N][N];

  for (int i = 0; i <= m; i++)
    dp[0][i] = 1;
  for (int i = 1; i <= n; i++)
  {
    dp[i][0] = 1;
    for (int j = 1; j <= m; j++)
    {
      // clang-format off
      // dp[i][j] = 
      //   dp[i - 1][j]
      // + 4 * j * dp[i - 1][j - 1]
      // + j * (i - 1) * dp[i - 2][j - 1];
      // clang-format on
      dp[i][j] += dp[i - 1][j];
      dp[i][j] += 4 * j * dp[i - 1][j - 1];
      if (i >= 2)
        dp[i][j] += j * (i - 1) * dp[i - 2][j - 1];
      if (j >= 2)
        dp[i][j] += j * (j - 1) / 2 * dp[i - 1][j - 2];
    }
  }

  std::cout << dp[n][m] - 1 << std::endl;

  return 0;
}
