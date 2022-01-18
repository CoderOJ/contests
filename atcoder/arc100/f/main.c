#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define N 25005
#define K 405

int n, k, m, ans, tot;
int a[N], f[N][K], g[N][K], vis[K];

bool check(int l, int r)
{
  memset(vis, 0, sizeof(vis));
  for (int i = l; i <= r; i++)
  {
    if (vis[a[i]])
      return false;
    vis[a[i]] = 1;
  }
  return true;
}

bool colorful()
{
  for (int i = 1; i + k - 1 <= m; i++)
    if (check(i, i + k - 1))
      return true;
  return false;
}

void solve(int (*f)[K])
{
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j < k; j++)
      f[i][j] =
          (1ll * (f[i - 1][j - 1] - f[i - 1][j] + MOD) * (k - j + 1) % MOD +
           f[i - 1][j]) %
          MOD;
    for (int j = k - 1; j >= 0; j--)
      f[i][j] = (f[i][j] + f[i][j + 1]) % MOD;
  }
}

int power(int a, int b)
{
  int r = 1;
  for (; b; b >>= 1)
  {
    if (b & 1)
      r = 1ll * r * a % MOD;
    a = 1ll * a * a % MOD;
  }
  return r;
}

int main()
{
  scanf("%d%d%d", &n, &k, &m);
  tot = 1ll * power(k, n - m) * (n - m + 1) % MOD;
  for (int i = 1; i <= m; i++)
    scanf("%d", &a[i]);
  if (colorful())
  {
    printf("%d\n", tot);
    return 0;
  }

  int l = m, r = 1;
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= m; i++)
  {
    if (vis[a[i]])
    {
      l = i - 1;
      break;
    }
    vis[a[i]] = 1;
  }

  memset(vis, 0, sizeof(vis));
  for (int i = m; i >= 1; i--)
  {
    if (vis[a[i]])
    {
      r = m - i;
      break;
    }
    vis[a[i]] = 1;
  }

  if (l == m)
  {
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j < k; j++)
      {
        f[i][j] =
            (1ll * (f[i - 1][j - 1] - f[i - 1][j] + MOD) * (k - j + 1) % MOD +
             f[i - 1][j]) %
            MOD;
        g[i][j] =
            (1ll * (g[i - 1][j - 1] - g[i - 1][j] + MOD) * (k - j + 1) % MOD +
             g[i - 1][j]) %
            MOD;
        if (j >= m)
          g[i][j] = (g[i][j] + f[i][j]) % MOD;
      }
      for (int j = k - 1; j >= 0; j--)
      {
        f[i][j] = (f[i][j] + f[i][j + 1]) % MOD;
        g[i][j] = (g[i][j] + g[i][j + 1]) % MOD;
      }
    }
    ans = g[n][0];
    for (int i = k; i > k - m; i--)
      ans = 1ll * power(i, MOD - 2) * ans % MOD;
  }
  else
  {
    for (int i = 0; i <= l; i++)
      f[0][i] = 1;
    for (int i = 0; i <= r; i++)
      g[0][i] = 1;
    solve(f);
    solve(g);
    for (int i = 0; i <= n - m; i++)
      ans = (ans + 1ll * f[i][0] * g[n - m - i][0]) % MOD;
  }

  printf("%d\n", (tot - ans + MOD) % MOD);

  return 0;
}
