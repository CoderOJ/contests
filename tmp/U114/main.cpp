#include <bits/stdc++.h>

const int MOD = 998244353;
const int N = 505;
int succ[N], a[N], n;
int pow2[N];
int gmax[N][N];
int f[N][N], g[N][N], h[N];
bool vis[N];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    int x;
    scanf("%d", &x);
    x--;
    succ[x] = i;
  }
  int c = 0;
  for (int i = 0; i < n; i++)
    if (!vis[i])
    {
      for (int p = succ[i]; p != i; p = succ[p])
      {
        a[c++] = p;
        vis[p] = true;
      }
      a[c++] = i;
      vis[i] = true;
    }
  pow2[0] = 1;
  for (int i = 1; i < N; i++)
    pow2[i] = (pow2[i - 1] * 2) % MOD;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j <= n; j++)
      for (int k = i; k < j; k++)
        gmax[i][j] += (a[k] > a[j - 1]);
  for (int i = n - 1; i >= 0; i--)
  {
    f[i][i] = 0;
    g[i][i] = 1;
    for (int j = i + 1; j <= n; j++)
    {
      f[i][j] = g[i][j - 1];
      for (int k = j - 1; k >= i; k--)
        if (k == i || a[k - 1] < a[j - 1])
          g[i][j] = (g[i][j] + 1ll * g[i][k] * f[k][j] % MOD * pow2[gmax[k][j]]) % MOD;
    }
  }
  h[0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 0; j < i; j++)
      if (j == 0 || a[j - 1] < a[i - 1])
        if (gmax[j][i] == (i - j - 1))
          h[i] = (h[i] + 1ll * h[j] * f[j][i]) % MOD;
  printf("%d\n", h[n]);
  return 0;
}
