#include <stdio.h>

#define N 50

char map[N][N];
int  sum[N][N];
int  n, m;
int  px, py;

int dp[N][N][N][N];

int get_sum(int xl, int xr, int yl, int yr)
{
  return sum[xr][yr] - sum[xl][yr] - sum[xr][yl] + sum[xl][yl];
}

int min(int a, int b)
{
  return a < b ? a : b;
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
  {
    scanf("%s", map[i]);
    for (int j = 0; j < m; j++)
      if (map[i][j] == 'P')
      {
        px = i;
        py = j;
      }
      else if (map[i][j] == '#')
      {
        sum[i + 1][j + 1] = 1;
      }
  }

  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++)
      sum[i + 1][j] += sum[i][j];
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++)
      sum[i][j + 1] += sum[i][j];

  for (int xl = n - 1; xl >= 0; xl--)
    for (int xr = xl + 1; xr <= n; xr++)
      for (int yl = m - 1; yl >= 0; yl--)
        for (int yr = yl + 1; yr <= m; yr++)
          if (xl <= px && px < xr && yl <= py && py < yr)
          {
            dp[xl][xr][yl][yr] =
                min(min(get_sum(xl, px + 1, yl, py + 1),
                        get_sum(xl, px + 1, py, yr)),
                    min(get_sum(px, xr, yl, py + 1), get_sum(px, xr, py, yr)));
            for (int xm = xl + 1; xm < xr; xm++)
              for (int ym = yl + 1; ym < yr; ym++)
              {
                if (px < xm && py < ym)
                  dp[xl][xr][yl][yr] =
                      min(dp[xl][xr][yl][yr],
                          dp[xl][xm][yl][ym] + get_sum(xm, xr, yl, ym) +
                              get_sum(xl, xm, ym, yr));
                else if (px >= xm && py >= ym)
                  dp[xl][xr][yl][yr] =
                      min(dp[xl][xr][yl][yr],
                          dp[xm][xr][ym][yr] + get_sum(xm, xr, yl, ym) +
                              get_sum(xl, xm, ym, yr));
                else if (px < xm && py >= ym)
                  dp[xl][xr][yl][yr] =
                      min(dp[xl][xr][yl][yr],
                          dp[xl][xm][ym][yr] + get_sum(xl, xm, yl, ym) +
                              get_sum(xm, xr, ym, yr));
                else
                  dp[xl][xr][yl][yr] =
                      min(dp[xl][xr][yl][yr],
                          dp[xm][xr][yl][ym] + get_sum(xl, xm, yl, ym) +
                              get_sum(xm, xr, ym, yr));
              }
            /* printf("dp[%d][%d][%d][%d] = %d\n", */
            /*        xl, */
            /*        xr, */
            /*        yl, */
            /*        yr, */
            /*        dp[xl][xr][yl][yr]); */
          }

  printf("%d\n", dp[0][n][0][m]);

  return 0;
}
