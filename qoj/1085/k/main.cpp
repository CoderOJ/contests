#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>

bool check_min(auto &a, auto b)
{
  if (b < a)
  {
    a = b;
    return true;
  }
  else
  {
    return false;
  }
}

const int N = 72;
const int M = 155;

int main()
{
  static int a[N];

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);

  int m = *std::max_element(a, a + n);

  static int dp[N][N][M];
  memset(dp, 0x3f, sizeof(dp));

  for (int i = 0; i < n; i++)
    dp[i][i + 1][a[i] / 2] = a[i];

  for (int len = 2; len <= n; len++)
    for (int il = 0, ir = len; ir <= n; il++, ir++)
    {
      for (int k = 0; k <= m; k++)
        check_min(
            dp[il][ir][std::max(k, a[ir - 1]) / 2],
            dp[il][ir - 1][k] + std::max(0, a[ir - 1] - k));
      for (int im = il + 1; im < ir; im++)
        for (int ax = 0; ax <= m; ax++)
          for (int bx = 0; ax + bx <= m; bx++)
            check_min(dp[il][ir][ax + bx], dp[il][im][ax] + dp[im][ir][bx]);
    }

  for (int ir = 1; ir <= n; ir++)
  {
    int ans = 0x3f3f3f3f;
    for (int k = 0; k <= m; k++)
      check_min(ans, dp[0][ir][k]);
    printf("%d ", ans);
  }
  puts("");

  return 0;
}
