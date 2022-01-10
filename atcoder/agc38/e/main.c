#include <stdio.h>

#define MOD 998244353
#define N 405

int power(int a, int k)
{
  int ans = 1;
  while (k)
  {
    if (k & 1)
      ans = 1ll * ans * a % MOD;
    a = 1ll * a * a % MOD;
    k >>= 1;
  }
  return ans;
}

int n;
int fac[N], ifac[N], inv[N];
int a[N], s, is;
int b[N], t;
int p[N][N];
int g[N];

int main()
{
  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1;
  for (int i = 2; i <= 400; i++)
  {
    inv[i]  = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
    fac[i]  = 1ll * fac[i - 1] * i % MOD;
    ifac[i] = 1ll * ifac[i - 1] * inv[i] % MOD;
  }

  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    scanf("%d%d", &a[i], &b[i]);
    s += a[i];
    t += b[i] - 1;
  }
  is = power(s, MOD - 2);

  p[0][0] = 1;
  int ts = 0, tt = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0, mul = 1; j <= b[i] - 1; j++)
    {
      g[j] = 1ll * mul * ifac[j] % MOD;
      mul  = 1ll * mul * a[i] % MOD * is % MOD;
    }
    ts += a[i];
    tt += b[i] - 1;
    for (int j = ts; j >= 0; j--)
    {
      for (int k = tt; k >= 0; k--)
      {
        int tmp = 0;
        for (int kk = 0; kk <= b[i] - 1 && kk <= k; kk++)
          tmp = (tmp + 1ll * g[kk] * p[j][k - kk] % MOD) % MOD;
        p[j][k] = (MOD - tmp) % MOD;
      }
      if (j >= a[i])
        for (int k = 0; k <= tt; k++)
          p[j][k] = (p[j][k] + p[j - a[i]][k]) % MOD;
    }
  }

  int ans = 0;
  for (int i = 0; i < s; i++)
  {
    const int x  = 1ll * i * is % MOD;
    int       f = power(1 - x + MOD, MOD - 2), ff = f;
    for (int j = 0; j <= t; j++)
    {
      ans = (ans + 1ll * p[i][j] * fac[j] % MOD * f % MOD) % MOD;
      f   = 1ll * f * ff % MOD;
    }
  }
  printf("%d\n", (MOD - ans) % MOD);
}
