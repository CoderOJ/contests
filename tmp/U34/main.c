#include <stdio.h>

#define N 262144
#define MOD 998244353

void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b, *b = tmp;
}

int test_dec(int a) 
{
  return a >= MOD ? a - MOD : a;
}

int test_inc(int a)
{
  return a < 0 ? a + MOD : a;
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

void dft(int a[], int n)
{
  int l = 1 << n;
  static int rev[N], g[N], last_n = -1;
  if (last_n != n)
  {
    last_n = n;
    int n_d1 = n - 1;
    for (int i=1; i<l; ++i)
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << n_d1);
    for (int i=1; i<l; i <<= 1)
    {
      int cur_g = power(3, MOD / (2 * i));
      g[i] = 1;
      for (int j=1; j<i; ++j)
        g[i + j] = 1ll * g[i + j - 1] * cur_g % MOD;
    }
  }

  for (int i=0; i<l; ++i)
    if (i < rev[i])
      swap(&a[i], &a[rev[i]]);

  for (int k=1; k<l; k<<=1)
  {
    int step = k * 2;
    for (int j=0; j<l; j += step)
      for (int i=0; i<k; ++i)
      {
        int tmp = 1ll * a[j + k + i] * g[k + i] % MOD; 
        a[j + k + i] = test_inc(a[j + i] - tmp);
        a[j + i] = test_dec(a[j + i] + tmp);
      }
  }
}

void idft(int a[], int n)
{
  int l = (1 << n);
  int *__begin = a + 1, *__end = a + l - 1;
  while (__begin < __end)
  {
    swap(__begin, __end);
    __begin++, __end--;
  }
  dft(a, n);
  int inv_l = power(l, MOD - 2);
  for (int i=0; i<l; ++i)
    a[i] = 1ll * a[i] * inv_l % MOD;
}

int a[N], b[N], an, bn;

int main()
{
  scanf("%d%d", &an, &bn); an++, bn++;
  tor (int i=0; i<an; ++i) scanf("%d", &a[i]);
  for (int i=0; i<bn; ++i) scanf("%d", &b[i]);

  int n = 1;
  while ((1 << n) < an + bn) n++;
  int l = 1 << n;

  dft(a, n);
  dft(b, n);
  for (int i=0; i<l; ++i)
    a[i] = 1ll * a[i] * b[i] % MOD;
  idft(a, n);

  for (int i=0; i<an+bn-1; ++i)
    printf("%d ", a[i]);
  return 0;
}
