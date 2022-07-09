#include <stdio.h>

#define N 20000005
#define MOD 1000000007

const int max_x = 2000000;

int x1, x2, x3, x4, x5, x6, y1, y2, y3, y4, y5, y6;
int ans;

int fac[N], nfac[N], inv[N];
int xx[9], yy[9], zz[9];

void set(int p, int x, int y, int z)
{
  xx[p] = x;
  yy[p] = y;
  zz[p] = z;
}

int abs(int x)
{
  return x < 0 ? -x : x;
}

int G(int a, int b, int c, int d)
{
  int x = abs(a - c);
  int y = abs(b - d);
  return (int)(1ll * fac[x + y] * nfac[x] % MOD * nfac[y] % MOD);
}

int calc(int sx, int sy, int x1, int y1, int x2, int y2, int tx, int ty, int f)
{
  int res = 0;
  for (int i = x1; i <= x2; i++)
    res =
        (res -
         1ll * G(sx, sy, i, y1 - 1) * G(i, y1, tx, ty) % MOD * (i + y1) % MOD +
         1ll * G(sx, sy, i, y2) * G(i, y2 + 1, tx, ty) % MOD * (i + y2 + 1) %
             MOD) %
        MOD;

  for (int i = y1; i <= y2; i++)
    res =
        (res -
         1ll * G(sx, sy, x1 - 1, i) * G(x1, i, tx, ty) % MOD * (x1 + i) % MOD +
         1ll * G(sx, sy, x2, i) * G(x2 + 1, i, tx, ty) % MOD * (x2 + i + 1) %
             MOD) %
        MOD;

  return (res * f + MOD) % MOD;
}

int main()
{
  inv[0] = fac[0] = nfac[0] = 1;
  inv[1] = fac[1] = nfac[1] = 1;
  for (int i = 2; i <= max_x; i++)
  {
    inv[i]  = 1ll * inv[MOD % i] * (MOD - MOD / i) % MOD;
    fac[i]  = 1ll * fac[i - 1] * i % MOD,
    nfac[i] = 1ll * nfac[i - 1] * inv[i] % MOD;
  }

  scanf(
      "%d%d%d%d%d%d%d%d%d%d%d%d",
      &x1,
      &x2,
      &x3,
      &x4,
      &x5,
      &x6,
      &y1,
      &y2,
      &y3,
      &y4,
      &y5,
      &y6);

  set(1, x1 - 1, y1 - 1, 1);
  set(2, x1 - 1, y2, -1);
  set(3, x2, y1 - 1, -1);
  set(4, x2, y2, 1);

  set(5, x5, y5, 1);
  set(6, x5, y6 + 1, -1);
  set(7, x6 + 1, y5, -1);
  set(8, x6 + 1, y6 + 1, 1);

  for (int i = 1; i <= 4; i++)
    for (int j = 5; j <= 8; j++)
      ans = (ans +
             calc(xx[i], yy[i], x3, y3, x4, y4, xx[j], yy[j], zz[i] * zz[j])) %
            MOD;

  printf("%d\n", (ans + MOD) % MOD);

  return 0;
}
