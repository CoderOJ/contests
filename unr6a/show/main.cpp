#include <bits/stdc++.h>

const int MOD = 998244353;

enum int_t : int
{
};

int_t operator+(int_t a, int_t b)
{
  int r = (int)a + (int)b;
  if (r >= MOD)
    r -= MOD;
  return (int_t)r;
}

int_t &operator+=(int_t &a, int_t b)
{
  a = a + b;
  return a;
}

int main()
{
  int n, m;
  static char ss[305];

  scanf("%d%d", &n, &m);
  scanf("%s", ss);
  int l = n + m * 2;

  static int pre[305];
  memset(pre, -1, sizeof(pre));
  for (int i = 0; i <= n; i++)
  {
    int c = 0;
    for (int j = i - 1; j >= 0; j--)
    {
      c += (ss[j] == '0') ? 1 : -1;
      if (c == 1)
      {
        pre[i] = j;
        break;
      }
    }
  }

  static int_t dp[905][305][305];
  dp[0][0][0] = (int_t)1;
  for (int i = 0; i < l; i++)
    for (int s = 0; s <= m; s++)
      for (int k = 0; k <= n; k++)
        if (dp[i][s][k] != (int_t)0)
        {
          if (k < n && ss[k] == '0')
            dp[i + 1][s][k + 1] += dp[i][s][k];
          else
            dp[i + 1][s + 1][k] += dp[i][s][k];

          if (k < n && ss[k] == '1')
            dp[i + 1][s][k + 1] += dp[i][s][k];
          else if (s > 0)
            dp[i + 1][s - 1][k] += dp[i][s][k];
          else if (pre[k] != -1)
            dp[i + 1][s + 1 - 1][pre[k]] += dp[i][s][k];
        }

  std::cout << (int)dp[l][0][n] << std::endl;

  return 0;
}
