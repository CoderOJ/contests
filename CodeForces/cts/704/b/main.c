#include <stdio.h>
#include <string.h>

#define int long long

void check_min(int *x, int y)
{
  if (y < *x)
    *x = y;
}

#define N 5005

int x[N], a[N], b[N], c[N], d[N];
int tl[N], tr[N], fl[N], fr[N];
int n, s, t;

int  _dp[2][N];
int *dp[N];

signed main()
{
  scanf("%lld%lld%lld", &n, &s, &t);
  s = s - 1;
  t = t - 1;

  for (int i = 0; i < n; i++)
    scanf("%lld", &x[i]);
  for (int i = 0; i < n; i++)
    scanf("%lld", &a[i]);
  for (int i = 0; i < n; i++)
    scanf("%lld", &b[i]);
  for (int i = 0; i < n; i++)
    scanf("%lld", &c[i]);
  for (int i = 0; i < n; i++)
    scanf("%lld", &d[i]);

  for (int i = 0; i < n; i++)
  {
    tl[i] = x[i] + c[i];
    tr[i] = -x[i] + d[i];
    fl[i] = x[i] + a[i];
    fr[i] = -x[i] + b[i];
  }

  for (int i = 0; i <= n; i++)
    dp[i] = _dp[i % 2];

  memset(dp[1], 0x3f, sizeof(_dp[0]));
  dp[1][1] = fr[0] + tr[0];
  for (int i = 1; i < n; i++)
  {
    memset(dp[i + 1], 0x3f, sizeof(_dp[0]));
    /* printf("%lld: %lld %lld %lld %lld\n", i, fl[i], fr[i], tl[i], tr[i]); */
    /* printf("dp[%lld]: %lld %lld\n", i, dp[i][1], dp[i][2]); */

    if (i > s && i > t)
      dp[i][1] = 0x3f3f3f3f3f3f3f3f;

    // from l, to l
    if (i != s && i != t)
    {
      for (int j = 2; j <= n; j++)
        check_min(&dp[i + 1][j - 1], dp[i][j] + fl[i] + tl[i]);
    }
    // from l, to r
    if (i != s)
    {
      int st = i > t ? 2 : 1;
      for (int j = st; j <= n; j++)
        check_min(&dp[i + 1][j], dp[i][j] + fl[i] + tr[i]);
    }
    // from r, to l
    if (i != t)
    {
      int st = i > s ? 2 : 1;
      for (int j = st; j <= n; j++)
        check_min(&dp[i + 1][j], dp[i][j] + fr[i] + tl[i]);
    }
    // from r, to r
    {
      for (int j = 1; j <= n; j++)
        check_min(&dp[i + 1][j + 1], dp[i][j] + fr[i] + tr[i]);
    }
  }

  printf("%lld\n", dp[n][1] - fr[s] - tr[t]);

  return 0;
}
