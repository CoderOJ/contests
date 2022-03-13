#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
using int_t       = cm::intm<MOD>;

CONSTRAINT(N, 100005, 105)

int   a[N], n;
int_t dp[N][2][2];

std::vector<int> occurs[N];

int main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    a[i] = sc.next_int();
    occurs[a[i]].emplace_back(i);
  }

  for (int i = 1; i <= n; i++)
  {
    if (occurs[i].size() > 2)
    {
      puts("0");
      return 0;
    }
    else if (occurs[i].size() == 2)
    {
      if (occurs[i][1] - occurs[i][0] != 2)
      {
        puts("0");
        return 0;
      }
    }
  }

  dp[1][0][1] = 1;
  for (int i = 1; i < n; i++)
  {
    for (int x0 = 0; x0 < 2; x0++)
      for (int x1 = 0; x1 < 2; x1++)
      {
        if ((x0 == 0 || (i >= 2 && a[i - 2] == a[i])) && a[i] != a[i + 2])
          dp[i + 1][x1][0] += dp[i][x0][x1];
        if (i < 2 || a[i] != a[i - 2])
          dp[i + 1][x1][1] += dp[i][x0][x1];
      }
    see(i + 1, dp[i + 1][0][0]);
    see(i + 1, dp[i + 1][0][1]);
    see(i + 1, dp[i + 1][1][0]);
    see(i + 1, dp[i + 1][1][1]);
  }

  int_t ans = dp[n][0][0] + dp[n][1][0];

  int free_cnt = 0;
  for (int i = 1; i <= n; i++)
    if (occurs[i].empty())
      free_cnt += 1;

  for (int i = 1; i <= free_cnt; i++)
    ans *= i;

  std::cout << ans << std::endl;

  return 0;
}
