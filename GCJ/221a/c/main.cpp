#include "/home/jack/cm/debug"
#include <bits/stdc++.h>

const int N = 105;
int a[N][N], d[N][N], dp[N][N], f[N];

int main()
{
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++)
  {
    int n, m;
    scanf("%d%d", &n, &m);
    int ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
      {
        scanf("%d", &a[i][j]);
        ans += a[i][j];
      }
    for (int i = 0; i < n; i++)
    {
      std::vector<int> mins(m, 0x3f3f3f3f);  
      for (int j = i; j < n; j++)
      {
        for (int k = 0; k < m; k++)
          mins[k] = std::min(mins[k], a[j][k]);
        d[i][j + 1] = std::accumulate(mins.begin(), mins.end(), 0);
        // printf("d[%d][%d] = %d\n", i, j + 1, d[i][j + 1]);
      }
    }
    memset(dp, 0, sizeof(dp));
    for (int l = n - 1; l >= 0; l--)
      for (int r = l + 1; r <= n; r++)
      {
        for (int m = l + 1; m < r - 1; m++)
          dp[l][r] = std::max(dp[l][r], dp[l][m] + dp[m][r]);
        int cc = d[l][r];
        memset(f, 0, sizeof(f));
        for (int i = l; i < r; i++)
        {
          f[i + 1] = f[i] + cc;
          for (int j = l; j < i + 1; j++)
            f[i + 1] = std::max(f[i + 1], f[j] + dp[j][i + 1] + cc);
        }
        dp[l][r] = std::max(dp[l][r], f[r] - cc);
      }
    // printf("ans = %d, dp[0][n] = %d\n", ans, dp[0][n]);
    printf("Case #%d: %d\n", i, (ans - dp[0][n]) * 2);
  }
  return 0;
}
