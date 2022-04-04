#include <bits/stdc++.h>

const int N = 200005;
const int B = 505;
int a[N], n, m, k;
int _dp[2][B];
int *(dp[N]);
int last_occur[N];
int min_l[N];

int main()
{
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);

  int ans = 0;

  memset(_dp, 0x3f, sizeof(_dp));
  for (int i = n; i >= 0; i--) dp[i] = _dp[i % 2];
  for (int i = n - 1; i >= 0; i--)
    for (int l = 2; l < B && i + l <= n; l++)
    {
      dp[i][l] = std::min({dp[i][l - 1], dp[i + 1][l - 1], std::abs(a[i + l - 1] - a[i])});
      if (l >= k) ans = std::max(ans, dp[i][l] * (l - 1));
    }

  memset(last_occur, -1, sizeof(last_occur));
  for (int i = 0; i < n; i++)
  {
    for (int p = std::max(1, a[i] - B); p <= std::min(m, a[i] + B); p++)
    {
      int &x = min_l[std::abs(a[i] - p) + 1];
      x = std::max(x, last_occur[p] + 1);
    }
    for (int j = 1; j < B; j++)
    {
      min_l[j] = std::max(min_l[j], min_l[j - 1]);
      if (i - min_l[j] + 1 >= k) 
        ans = std::max(ans, (i - min_l[j]) * j);
    }
    last_occur[a[i]] = i;
  }

  std::cout << ans << std::endl;

  return 0;
}
