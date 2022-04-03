#include <bits/stdc++.h>

const int MOD = 998244353;
const int N = 6005;
int stir[N][N];
int n, m;

int main()
{
  scanf("%d%d", &n, &m);
  n++, m++;
  stir[0][0] = 1;
  for (int i = 1; i <= n; i++)
  {
    stir[i][0] = 0;
    for (int j = 1; j <= i; j++)
      stir[i][j] = (stir[i - 1][j - 1] + 1ll * stir[i - 1][j] * j) % MOD;
  }
  int ans = 0;
  for (int i = 0; i <= m; i++)
    ans = (ans + 1ll * stir[(n + 1) / 2][i] * stir[n / 2][m - i]) % MOD;
  for (int i = 1; i < m; i++)
    ans = 1ll * ans * i % MOD;
  std::cout << ans << std::endl;
  return 0;
}
