#include <stdio.h>
#include <stdlib.h>

#define N 1005

long long x[N], y[N];
int       n;

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    scanf("%lld%lld", &x[i], &y[i]);
    x[i] = -x[i];
    y[i] = -y[i];
  }

  int s_v2 = 0;
  for (int i = 0; i < n; i++)
    s_v2 += llabs(x[i]) % 2 == llabs(y[i]) % 2;

  if (s_v2 != 0 && s_v2 != n)
  {
    puts("-1");
    return 0;
  }

  if (s_v2)
    for (int i = 0; i < n; i++)
      x[i]++;

  printf("%d\n", 35 + !!s_v2);
  if (s_v2)
    printf("1 ");
  for (int i = 34; i >= 0; i--)
    printf("%lld ", 1ll << i);
  putchar_unlocked('\n');

  for (int i = 0; i < n; i++)
  {
    if (s_v2)
      putchar_unlocked('R');
    for (int j = 34; j >= 0; j--)
    {
      long long t = 1ll << j;
      if (llabs(x[i]) > llabs(y[i]))
      {
        if (x[i] > 0)
        {
          x[i] -= t;
          putchar_unlocked('L');
        }
        else
        {
          x[i] += t;
          putchar_unlocked('R');
        }
      }
      else
      {
        if (y[i] > 0)
        {
          y[i] -= t;
          putchar_unlocked('D');
        }
        else
        {
          y[i] += t;
          putchar_unlocked('U');
        }
      }
    }
    putchar_unlocked('\n');
  }

  return 0;
}
