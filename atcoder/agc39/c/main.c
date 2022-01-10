#include <stdio.h>
#include <string.h>

#define N 200005
#define MOD 998244353

int  n;
char a[N], t[N];
int  pa[N];
int  cnt[N];

int main()
{
  scanf("%d", &n);
  scanf("%s", a);

  pa[0] = 0;
  for (int i = 0; i < n; i++)
    pa[i + 1] = (pa[i] * 2 + (a[i] - '0')) % MOD;

  for (int i = 1; i <= n; i++)
    if (n % i == 0 && n / i % 2 == 1)
    {
      memcpy(t, a, i);
      for (int j = i; j < n; j++)
        t[j] = t[j - i] == '0' ? '1' : '0';
      if (memcmp(a, t, n) >= 0)
        cnt[i] = pa[i] + 1;
      else
        cnt[i] = pa[i];
    }

  for (int i = 1; i <= n; i++)
    for (int j = i * 2; j <= n; j += i)
      if (cnt[j])
        cnt[j] = (cnt[j] - cnt[i] + MOD) % MOD;

  /* for (int i = 1; i <= n; i++) */
  /*   printf("%d%c", cnt[i], " \n"[i == n]); */

  int ans = 0;
  for (int i = 1; i <= n; i++)
    ans = (ans + cnt[i] * 2ll * i) % MOD;
  printf("%d\n", ans);

  return 0;
}
