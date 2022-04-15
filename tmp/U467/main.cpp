#include <bits/stdc++.h>

const int MOD = 998244353;
const int inv2 = (MOD + 1) / 2;
const int N = 100005;

int f[N * 2], g[N * 2], h[N * 2];

void push_h(int u, int mul)
{
  h[u] = 1ll * h[u] * mul % MOD;
  g[u] = (1ll * g[u] * mul + (1 - mul)) % MOD;
}

void push_down(int u, int ls, int rs)
{
  if (h[u] != 1)
  {
    push_h(ls, h[u]);
    push_h(rs, h[u]);
    h[u] = 1;
  }
}

void make_modify(int u, int l, int r, int ml, int mr, int64_t &sum)
{
  if (ml <= l && r <= mr)
  {
    sum -= f[u];
    f[u] = 1ll * (1 + f[u]) * inv2 % MOD;
    push_h(u, inv2);
    sum += f[u];
  }
  else
  {
    int m = (l + r - 1) / 2 + 1;
    push_down(u, u + 1, u + (m - l) * 2);

    sum -= f[u];
    f[u] = 1ll * (0 + f[u]) * inv2 % MOD;
    g[u] = 1ll * (0 + g[u]) * inv2 % MOD;
    sum += f[u];

    if (ml < m) 
    {
      make_modify(u + 1, l, m, ml, mr, sum);
    }
    else
    {
      sum -= f[u + 1];
      f[u + 1] = 1ll * (g[u + 1] + f[u + 1]) * inv2 % MOD;
      sum += f[u + 1];
    }
    if (mr > m)
    {
      make_modify(u + (m - l) * 2, m, r, ml, mr, sum);
    }
    else
    {
      sum -= f[u + (m - l) * 2];
      f[u + (m - l) * 2] = 1ll * (g[u + (m - l) * 2] + f[u + (m - l) * 2]) * inv2 % MOD;
      sum += f[u + (m - l) * 2];
    }
  }
}

int main()
{
  std::fill(h, h + N * 2, 1);

  int n, m;
  scanf("%d%d", &n, &m);
  int64_t sum = 0;
  int mul = 1;
  for (int i = 0; i < m; i++)
  {
    int opt;
    scanf("%d", &opt);
    if (opt == 1)
    {
      int l, r;
      scanf("%d%d", &l, &r);
      l--;

      make_modify(1, 0, n, l, r, sum);
      mul = mul * 2 % MOD;
    }
    else
    {
      int ans = (sum % MOD) * mul % MOD;
      ans = (ans + MOD) % MOD;
      printf("%d\n", ans);
    }
  }
  return 0;
}
