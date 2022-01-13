#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define N 75
#define M 205
#define MOD 1000000007

int  n, m;
int  st[N], cnt[N], w[N], C[M][M], dp[N][N][N];
bool vs[N];
char a[N];

void iaddmodl(int *x, int y)
{
  *x = *x + y;
  if (*x >= MOD)
    *x = *x - MOD;
}

int slv(int x1, int x2)
{
  if (!x1 && !x2)
    return 1;
  int nw = 0, res = 0;
  st[0] = 0;
  memset(vs, 0, sizeof(vs));
  memset(dp, 0, sizeof(dp));
  for (int i = 1, ps; i <= m; ++i)
    if (a[i] == 'r')
    {
      if (nw < x1)
      {
        ps = 0;
        ++nw;
        for (int j = i + 1; j <= m; ++j)
          if (a[j] == 'b' && !vs[j])
          {
            ps = j;
            break;
          }
        if (!ps)
          return 0;
        vs[i] = vs[ps] = 1;
        st[++st[0]]    = ps;
      }
      else if (nw < x1 + x2)
        ++nw, vs[i] = 1;
    }

  if (nw < x1 + x2)
    return 0;
  for (int i = m; i; --i)
    cnt[i] = cnt[i + 1] + (!vs[i]);
  for (int i = 1; i <= st[0]; ++i)
    w[i] = cnt[st[st[0] - i + 1]] + i;

  dp[0][0][0] = 1;
  for (int i = 0; i < st[0]; ++i)
    for (int j = 0; j <= w[i] && (j + x2) * 2 - 1 <= n; ++j)
      for (int k = 1, s = dp[i][j][0];
           j + k <= w[i + 1] && (j + k + x2) * 2 - 1 <= n;
           ++k)
      {
        for (int l = 1; i + l <= st[0] && j + k * l <= w[i + l] &&
                        (j + k * l + x2) * 2 - 1 <= n;
             ++l)
          iaddmodl(&dp[i + l][j + k * l][k], 1ll * s * C[i + l][l] % MOD);
        iaddmodl(&s, dp[i][j][k]);
      }

  for (int i = 0, s, t1, t2; i <= w[st[0]] && (i + x2) * 2 - 1 <= n; ++i)
  {
    s  = 0;
    t1 = (i + x2) * 2 - 1;
    t2 = x1 * 2 + 2;
    for (int j = 0; j <= i; ++j)
      iaddmodl(&s, dp[st[0]][i][j]);
    iaddmodl(&res, 1ll * s * C[n + t2 - 1][t1 + t2 - 1] % MOD);
  }

  res = 1ll * res * C[x1 + x2][x1] % MOD;
  return res;
}

int main()
{
  scanf("%d %d %s", &n, &m, a + 1);
  for (int i = 0; i < M; ++i)
  {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
  }

  int ans = 0;
  for (int i = 0; i * 2 <= m; ++i)
    for (int j = 0; i * 2 + j <= m; ++j)
      iaddmodl(&ans, slv(i, j));
  printf("%d\n", ans);
  return 0;
}
