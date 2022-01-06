#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cmath>
#include <cstring>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 505;

int n, mod, dp[N][N];

std::pair<int, int> p[N];

void init()
{
  for (int i = 0; i < n; i++)
  {
    p[i + 1].first  = static_cast<int>(ceil(sqrt(n * n - i * i)) - 1);
    p[i + 1].second = static_cast<int>(floor(sqrt(4 * n * n - i * i)));
    if (p[i + 1].second > 2 * n - 1)
      p[i + 1].second = 2 * n - 1;
  }
  for (int i = n; i < 2 * n; i++)
  {
    p[i + 1].first = static_cast<int>(floor(sqrt(4 * n * n - i * i)));
    if (p[i + 1].first > 2 * n - 1)
      p[i + 1].first = 2 * n - 1;
    p[i + 1].second = 0;
  }
  std::sort(p + 1, p + 2 * n + 1);
}

int Calc(int k)
{
  memset(dp, 0, sizeof(dp));
  dp[0][0]   = 1;
  int limcnt = 0, cntr = 0;
  for (int i = 1; i <= 2 * n; i++)
  {
    if (p[i].second == 0)
    {
      for (int j = 0; j <= limcnt; j++)
        dp[i][j] =
            (dp[i][j] + 1ll * dp[i - 1][j] * (p[i].first - cntr - j + 1)) % mod;
      cntr++;
    }
    else
    {
      for (int j = 0; j <= limcnt; j++)
      {
        dp[i][j] = (dp[i][j] + 1ll * dp[i - 1][j] *
                                   (p[i].second + 1 - n - k - limcnt + j)) %
                   mod;
        dp[i][j + 1] =
            (dp[i][j + 1] + 1ll * dp[i - 1][j] * (p[i].first - cntr - j + 1)) %
            mod;
      }
      limcnt++;
    }
  }
  return dp[2 * n][k];
}

void solve()
{
  long long ans = 0;
  for (int i = 0; i <= n; i++)
  {
    if (i & 1)
      ans = (ans - Calc(i) + mod) % mod;
    else
      ans = (ans + Calc(i)) % mod;
  }
  printf("%lld", ans);
}

int main()
{
  n   = sc.next_int();
  mod = sc.next_int();
  init();
  solve();
  return 0;
}
