#include <bits/stdc++.h>

uint64_t x0;
uint64_t gen()
{
  const uint64_t MOD = 998244353;
  x0 = (100000005 * x0 + 20150823) % MOD;
  return x0 / 100;
}

const int MOD = 998244353;
const int N = 305;
int n, m, q;
int dp[N][N][N * 2];

int isubml(int64_t x)
{
  return x % MOD;
}

int main()
{
  scanf("%d%d%d", &n, &m, &q);
  scanf("%" SCNu64, &x0);
  for (int i = 0; i < q; i++)
  {
    int x = gen() % n + 1;
    int y = gen() % m + 1;
    int k = gen() % (n + m - x - y + 1);
    dp[x][y][k] += 1;
  }
  
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
    {
      for (int k = 0; k + 1 < n + m; k++)
        dp[i][j][k] = isubml(0ll + dp[i][j][k] + dp[i - 1][j][k + 1] + dp[i][j - 1][k + 1]);
      dp[i][j][0] = isubml(0ll + dp[i][j][0] + dp[i - 1][j][0] + dp[i][j - 1][0]);
    }

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      printf("%d%c", dp[i][j][0], " \n"[j == m]);

  return 0;
}
