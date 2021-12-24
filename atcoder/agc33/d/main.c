#include <stdio.h>

#define B 18
#define N 186
char map[N][N];
int n, m;

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

// dp[a][k][i][j] -> max right bound when ans is a, row i-j column k
int dp[B][N][N][N];

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%s", map[i]);

  for (int i = 0; i < n; i++)
    for (int j = 0; j <= n; j++)
      dp[0][m][i][j] = m;
  for (int k = 0; k < m; k++)
    for (int i = 0; i < n; i++)
    {
      dp[0][k][i][i] = m;
      for (int j = i; j < n; j++)
      {
        int cur_r = k;
        while (cur_r < m && map[j][k] == map[j][cur_r])
          cur_r++;
        if (map[i][k] == map[j][k])
          dp[0][k][i][j + 1] = min(dp[0][k][i][j], cur_r);
        else
          dp[0][k][i][j + 1] = k;
      }
    }

  for (int a = 0; a + 1 < B; a++)
  {
    for (int i = 0; i < n; i++)
      for (int j = 0; j <= n; j++)
        dp[a + 1][m][i][j] = m;
    for (int k = 0; k < m; k++)
      for (int i = 0; i < n; i++)
      {
        dp[a + 1][k][i][i] = m;
        int best_sp = i;
        for (int j = i; j < n; j++)
        {
          while (best_sp < j &&
                 min(dp[a][k][i][best_sp + 1], dp[a][k][best_sp + 1][j + 1]) >=
                     min(dp[a][k][i][best_sp], dp[a][k][best_sp][j + 1]))
            best_sp++;
          dp[a + 1][k][i][j + 1] =
              max(dp[a][dp[a][k][i][j + 1]][i][j + 1],
                  min(dp[a][k][i][best_sp], dp[a][k][best_sp][j + 1]));
        }
      }
  }

  /* for (int a = 0; a < 3; a++) */
  /*   for (int k = 0; k < m; k++) */
  /*     for (int i = 0; i < n; i++) */
  /*       for (int j = i; j <= n; j++) */
  /*         printf("dp[%d][%d][%d][%d] = %d\n", a, k, i, j, dp[a][k][i][j]); */

  for (int i = 0; i < B; i++)
    if (dp[i][0][0][n] == m)
    {
      printf("%d\n", i);
      return 0;
    }

  return 0;
}
