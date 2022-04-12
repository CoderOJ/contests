#include <bits/stdc++.h>

const int MOD = 998244353;
const int inv2 = (MOD + 1) / 2;
const int N = 16;
uint32_t e[N];
int n, m;

int cyc[1 << N][N];
int dp[1 << N];

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    u--, v--;
    e[u] |= (1 << v);
    e[v] |= (1 << u);
  }

  for (int i = 0; i < n; i++)
    cyc[1 << i][i] = 1;
  for (uint32_t i = 1; i < (1 << n); i++)
  {
    int s = __builtin_ctz(i);
    for (int u = s; u < n; u++)
      if (cyc[i][u])
        for (int v = s + 1; v < n; v++)
          if ((e[u] & (1 << v)) && !(i & (1 << v)))
            (cyc[i | (1 << v)][v] += cyc[i][u]) %= MOD;
  }

  for (int i = 0; i < (1 << n); i++)
    if (__builtin_popcount(i) >= 3)
    {
      int s = __builtin_ctz(i);
      for (int t = s + 1; t < n; t++)
        if (e[t] & (1 << s))
        {
          (dp[i] += cyc[i][t]) %= MOD;
        }
      dp[i] = 1ll * dp[i] * inv2 % MOD;
    }

  int ans = 0;
  for (uint32_t i = 0; i < (1 << n); i++)
  {
    int pc = __builtin_popcount(i);
    if (pc >= 3)
    {
      ans = (ans + ((1ll * dp[i]) << pc)) % MOD;
      static int t[1 << N];
      t[0] = 1;

      if (dp[i])
      {
        for (uint32_t j = (i + 1) | i; j < (1 << n); j = (j + 1) | i)
        {
          uint32_t k = j ^ i;
          int kt = __builtin_ctz(k);
          t[k] = (1ll * t[k ^ (1 << kt)] * __builtin_popcount(e[kt] & i)) % MOD;
          int cur = 1ll * t[k] * dp[i] % MOD;
          if (__builtin_popcount(k) % 2 == 0) cur = MOD - cur;
          dp[j] = (dp[j] + cur) % MOD;
          // printf("dp[%d] -> dp[%d]: %d\n", i, j, cur);
          ans = (ans - ((1ll * cur) << __builtin_popcount(i))) % MOD;
        }
      }
    }
  }

  printf("%d\n", (ans + MOD) % MOD);

  return 0;
}
