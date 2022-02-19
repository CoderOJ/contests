#include <stdio.h>

#define MOD 1000000007
#define N 105
#define M 5005

typedef int int_t;

int_t dp[N][M];

int n, m;

int main()
{
  scanf("%d%d", &n, &m);

  dp[n + 1][0] = 1;
  for (int i = n; i >= 1; i--)
    for (int j = 0; j < M; j++)
      if (dp[i + 1][j])
        for (int k = 0; k <= m; k++)
        {
          int vj = j;
          if (k <= i)
            vj += (k + j) / i;
          dp[i][vj] = (dp[i][vj] + dp[i + 1][j]) % MOD;
        }

  int_t ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j <= m; j++)
      ans = (ans + j) % MOD;
  for (int i = 0; i < n - 1; i++)
    ans = 1ll * ans * (m + 1) % MOD;

  for (int i = 0; i < M; i++)
    ans = (ans - 1ll * i * dp[1][i]) % MOD;
  ans = (ans + MOD) % MOD;

  printf("%d\n", ans);

  return 0;
}
