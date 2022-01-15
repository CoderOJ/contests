#include <stdio.h>

#define N 3005

int n, ans, mod;
int f[N], g[N][N], binom[N][N];

int mul(int x, int y)
{
  return 1ll * x * y % mod;
}

int ipowmodl(int x, int y, int p)
{
  int res = 1;
  for (; y; y >>= 1, x = 1ll * x * x % p)
    if (y & 1)
      res = 1ll * res * x % p;
  return res;
}

int main()
{
  scanf("%d%d", &n, &mod);

  for (int i = 0; i <= n; ++i)
  {
    binom[i][0] = g[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod,
      g[i][j]     = (g[i - 1][j - 1] + mul(j + 1, g[i - 1][j])) % mod;
  }

  for (int i = 0; i <= n; ++i)
  {
    int tmp = ipowmodl(2, ipowmodl(2, n - i, mod - 1), mod);
    int num = ipowmodl(2, n - i, mod), qaq = 1, res = 0;

    for (int j = 0; j <= i; ++j)
      res = (res + mul(g[i][j], qaq)) % mod, qaq = mul(qaq, num);
    ans = (ans +
           mul(mul((i % 2 == 1) ? mod - binom[n][i] : binom[n][i], tmp), res)) %
          mod;
  }

  printf("%d\n", ans);

  return 0;
}
