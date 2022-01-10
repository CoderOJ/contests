#include <stdio.h>

#define N 1000005
#define MOD 998244353

int n;
int a[N];
int m[N];
int s[N];
int inv[N];

int main()
{
  int i, j, r, s;
  scanf("%d", &n);
  s = 0;
  for (i = 0; i < n; i++)
  {
    int x;
    scanf("%d", &x);
    a[x]++;
    s += x;
    if (s >= MOD)
      s -= MOD;
  }

  inv[1] = 1;
  for (i = 2; i <= N; i++)
    inv[i] = (long long)(MOD - MOD / i) * inv[MOD % i] % MOD;

  for (i = 1; i <= N; i++)
  {
    a[i] = (long long)i * a[i] % MOD;
    for (j = 2 * i; j <= N; j += i)
      a[i] = (a[i] + (long long)j * a[j]) % MOD;
  }

  for (i = 1; i <= N; i++)
    a[i] = ((long long)a[i] * a[i]) % MOD;

  r = MOD - s;
  for (i = N; i; i--)
  {
    for (j = 2 * i; j <= N; j += i)
    {
      a[i] -= a[j];
      if (a[i] < 0)
        a[i] += MOD;
    }
    r = (r + (long long)inv[i] * a[i]) % MOD;
  }

  printf("%d\n", r % 2 == 1 ? (r + MOD) / 2 : r / 2);

  return 0;
}
