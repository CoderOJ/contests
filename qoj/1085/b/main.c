#include <stdint.h>
#include <stdio.h>

#define N 405

int n, m, mod;
int inv_pow[N][N], i_pow[N][N], binom[N][N];
int sf[N][N], f[N][N], h[N];

int main()
{
  scanf("%d%d%d", &n, &m, &mod);
  inv_pow[1][1] = 1;
  for (int i = 2; i <= n; i++)
    inv_pow[i][1] = mod - 1ll * (mod / i) * inv_pow[mod % i][1] % mod;

  for (int i = 1; i <= n; i++)
  {
    inv_pow[i][0] = i_pow[i][0] = 1, i_pow[i][1] = i;
    for (int j = 2; j <= n; j++)
    {
      inv_pow[i][j] = 1ll * inv_pow[i][j - 1] * inv_pow[i][1] % mod;
      i_pow[i][j]   = 1ll * i_pow[i][j - 1] * i % mod;
    }
  }

  for (int i = 0; i <= n; i++)
    for (int j = binom[i][0] = 1; j <= i; j++)
      binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % mod;

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      f[i][j] = i_pow[j][i];
      for (int k = 1; k <= j; k++)
      {
        f[i][j] = (f[i][j] //
                   - (int64_t)i_pow[k][i] * (sf[j - k + 1][k] - sf[j - k][k])
                   + (int64_t)i_pow[k - 1][i]
                         * (sf[j - k + 1][k - 1] - sf[j - k][k - 1]))
                % mod;
      }
    }
    for (int j = 1; j <= n; j++)
      for (int k = 1; k <= n; k++)
        sf[j][k] = (sf[j][k] + (int64_t)f[i][j] * inv_pow[k][i]) % mod;
  }

  int res = 1, ans = 0;
  for (int i = 1; i <= n; i++)
  {
    res  = (int64_t)res * (m - i + 1) % mod * inv_pow[i][1] % mod;
    h[i] = f[n][i];
    for (int j = 1; j < i; j++)
      h[i] = (h[i] - 1ll * h[j] * binom[i][j]) % mod;
    ans = (ans + 1ll * h[i] * res) % mod;
  }

  if (ans < 0)
    ans += mod;

  printf("%d\n", ans);
}
