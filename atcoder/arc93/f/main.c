#include <stdio.h>

#define MOD 1000000007
#define N 18

int fac[1 << 16 | 1], ifac[1 << 16 | 1];
int a[N], dp[N][1 << 16];
int n, m;

int power(int a, int b, int p)
{
  int ans = 1;
  for (; b; b >>= 1, a = 1ll * a * a % p)
    if (b & 1)
      ans = 1ll * ans * a % p;
  return ans;
}

void init(int n)
{
  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= n; i++)
    fac[i] = 1ll * fac[i - 1] * i % MOD;
  ifac[n] = power(fac[n], MOD - 2, MOD);
  for (int i = n - 1; i; i--)
    ifac[i] = 1ll * ifac[i + 1] * (i + 1) % MOD;
}

int ncr(int n, int m)
{
  if (n < m || m < 0)
    return 0;
  return 1ll * fac[n] * ifac[m] % MOD * ifac[n - m] % MOD;
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++)
    scanf("%d", &a[i]);

  init(1 << n);

  dp[m + 1][0] = 1;
  for (int i = m; i >= 1; i--)
    for (int j = 0; j < (1 << n); j++)
    {
      dp[i][j] = (dp[i][j] + dp[i + 1][j]) % MOD;
      for (int k = 0; k < n; k++)
        if ((j & (1 << k)) == 0)
          dp[i][j | (1 << k)] =
              (dp[i][j | (1 << k)] +
               1ll * dp[i + 1][j] * ncr((1 << n) - j - a[i], (1 << k) - 1) %
                   MOD * fac[1 << k]) %
              MOD;
    }

  long long ans = 0;
  for (int i = 0; i < (1 << n); i++)
  {
    int cnt = 0;
    for (int j = i; j; j -= j & -j)
      cnt = cnt + 1;
    if (cnt % 2 == 1)
      ans -= 1ll * dp[1][i] * fac[(1 << n) - i - 1] % MOD;
    else
      ans += 1ll * dp[1][i] * fac[(1 << n) - i - 1] % MOD;
  }

  ans = (ans % MOD + MOD) % MOD;
  printf("%lld\n", ans * (1 << n) % MOD);

  return 0;
}
