#include <stdio.h>

#define N 105

int n, m, k;
int mod;

int imodq(long long a)
{
  a %= mod;
  if (a < 0)
    a += mod;
  return (int)a;
}
int ipowl(int a, int b)
{
  int r = 1;
  for (; b > 0; b >>= 1)
  {
    if (b % 2 == 1)
      r = 1ll * r * a % mod;
    a = 1ll * a * a % mod;
  }
  return r;
}
int iinvl(int x)
{
  return ipowl(x, mod - 2);
}

int  binom[N][N];
void init_binom()
{
  for (int i = 0; i < N; i++)
  {
    binom[i][0] = 1;
    for (int j = 1; j <= i; j++)
      binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % mod;
  }
}

int  coef_row[N][N][N];
int  coef_column[N][N][N];
void init_coef()
{
  for (int t = 1; t <= k; t++)
    for (int i = 0; i <= m; i++)
    {
      int mul = imodq(1ll * ipowl(k - t + 1, i) *
                      (ipowl(t, m - i) - ipowl(t - 1, m - i)));

      coef_row[t][i][0] = 1;
      for (int j = 1; j <= n; j++)
        coef_row[t][i][j] = 1ll * coef_row[t][i][j - 1] * mul % mod;
    }
  for (int t = 1; t <= k; t++)
    for (int i = 0; i <= n; i++)
    {
      int mul = imodq(1ll * ipowl(t, n - i) *
                      (ipowl(k - t + 1, i) - ipowl(k - t, i)));

      coef_column[t][i][0] = 1;
      for (int j = 1; j <= m; j++)
        coef_column[t][i][j] = 1ll * coef_column[t][i][j - 1] * mul % mod;
    }
}

int  f[N][N][N];
int  g[N][N][N];
void make_dp()
{
  f[1][0][0] = 1;
  for (int t = 1; t <= k; t++)
    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= m; j++)
      {
        // clang-format off
        for (int l = 0; l + i <= n; l++)
        {
          g[t][i + l][j] = (g[t][i + l][j] +
            1ll * f[t][i][j] * binom[n - i][l] % mod * coef_row[t][j][l]) 
            % mod;
          /* printf("%d %d %d %d += %d %d %d\n", t, i, j, l, f[t][i][j], binom[n - i][l], coef_row[t][j][l]); */
        }
        for (int l = 0; l + j <= m; l++)
        {
          f[t + 1][i][j + l] = (f[t + 1][i][j + l] + 
            1ll * g[t][i][j] * binom[m - j][l] % mod * coef_column[t][i][l])
            % mod;
          /* printf("%d %d %d %d += %d %d %d\n", t, i, j, l, g[t][i][j], binom[m - j][l], coef_column[t][i][l]); */
        }
        // clang-format on
      }
}

int main()
{
  scanf("%d%d%d", &n, &m, &k);
  scanf("%d", &mod);

  init_binom();
  init_coef();
  make_dp();

  printf("%d\n", f[k + 1][n][m]);
  return 0;
}
