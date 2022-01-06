#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <limits>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

#define int long long

constexpr int N = 505;

int n, a[N][N], pa[N][N], ua[N][N];
int dp[N][N];

signed main()
{
  n = sc.next_int();
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (i != j)
        a[i][j] = sc.next_long();

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      pa[i][j] = pa[i - 1][j] + pa[i][j - 1] - pa[i - 1][j - 1] + a[i][j];
  for (int j = 1; j <= n; j++)
    for (int i = j; i >= 1; i--)
      ua[i][j] = ua[i + 1][j] + ua[i][j - 1] - ua[i + 1][j - 1] + a[i][j];

  auto get_cost = [](int k, int j, int i) {
    long long cost_up = ua[j + 1][i];
    long long cost_dw = (pa[n][j] - pa[n][k]) - (pa[i][j] - pa[i][k]);
    return cost_up + cost_dw;
  };

  int ans = std::numeric_limits<int>::max();

  for (int i = 1; i <= n; i++)
  {
    dp[i][0] = get_cost(0, 0, i);
    check_min(ans, dp[i][0] + get_cost(0, i, n));
    for (int j = 1; j < i; j++)
    {
      dp[i][j] = std::numeric_limits<int>::max();
      for (int k = 0; k < j; k++)
        check_min(dp[i][j], dp[j][k] + get_cost(k, j, i));
      check_min(ans, dp[i][j] + get_cost(j, i, n));
    }
  }

  std::cout << ans << std::endl;

  return 0;
}
