#include <stdint.h>
#include <stdio.h>

#define MOD 1000000007

int64_t f[3005][3005][2];

int main()
{
  int n, m;
  scanf("%d%d\n", &n, &m);

  for (int i = 0; i <= n; i++)
    f[0][i][i == 0] = 1;

  for (int i = 0; i < m; i++)
    for (int j = 0; j <= n; j++)
      for (int k = 0; k < 2; k++)
        if (f[i][j][k])
        {
          int x = (int)(f[i][j][k] % MOD);
          if (j)
          {
            f[i + 1][j - 1][k || j == 1] += x;
            f[i + 1][j][k || j == 1] += x;
          }
          if (j < n)
          {
            f[i + 1][j][k] += x;
            f[i + 1][j + 1][k] += x;
          }
        }

  int ans = 0;
  for (int i = 0; i <= n; i++)
    ans = (int)((ans + f[m][i][1]) % MOD);

  printf("%d\n", ans);
}
