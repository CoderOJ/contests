#include <stdio.h>

#define N 155

int n, k, mod;

int max(int a, int b)
{
  return a > b ? a : b;
}

void iaddmd(int *a, int b)
{
  *a = (*a + b) % mod;
}

void solve_even()
{
  k /= 2;

  static int f[N][N];
  f[0][0] = 1;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j <= k; j++)
      f[i + 1][0] = (f[i + 1][0] + f[i][j]) % mod;
    for (int j = 0; j < k; j++)
      f[i + 1][j + 1] = (f[i + 1][j + 1] + f[i][j]) % mod;
  }

  int ans0 = 0;
  for (int i = 0; i <= k; i++)
    ans0 = (ans0 + f[n / 2][i]) % mod;
  int ans1 = 0;
  for (int i = 0; i <= k; i++)
    ans1 = (ans1 + f[n - n / 2][i]) % mod;

  printf("%lld\n", (long long)ans0 * ans1 % mod);
}

void solve_odd()
{
  static int f[N * 2][N][N];
  f[0][0][0] = 1;

  const int kk = k;

  int cur = 0;
  for (int i = 0; i < n + kk - 1; i += 2)
  {
    cur = i + 2;
    for (int j = 0; j <= n; j++)
      for (int k = 0; k <= kk + 1; k++)
        iaddmd(&f[i + 2][0][0], f[i][j][k]);
    if (i + 2 <= n)
      for (int j = 0; j <= n; j++)
        for (int k = 0; k <= kk + 1; k++)
          iaddmd(&f[i + 2][j + 1][0], f[i][j][k]);
    if (i + 2 >= kk + 1)
      for (int j = 0; j <= n; j++)
      {
        for (int k = 1; k <= kk; k++)
          iaddmd(&f[i + 2][0][k + 1], f[i][j][k]);
        iaddmd(&f[i + 2][0][0], f[i][j][0]);
      }
    if (i + 2 >= kk + 1 && i + 2 <= n)
      for (int j = 0; j <= n; j++)
        for (int k = 0; max(k, j + 1) <= kk; k++)
          iaddmd(&f[i + 2][j + 1][max(k + 1, j + 2)], f[i][j][k]);
  }

  int sum = 0;
  for (int j = 0; j <= n; j++)
    for (int k = 0; k <= kk + 1; k++)
      iaddmd(&sum, f[cur][j][k]);
  printf("%d\n", sum);
}

int main()
{
  scanf("%d%d%d", &n, &k, &mod);

  if (k % 2 == 0)
    solve_even();
  else
    solve_odd();

  return 0;
}
