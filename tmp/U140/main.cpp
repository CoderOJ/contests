#include <bits/stdc++.h>

int64_t digit[26], n, kk;
int64_t dp[26][1000][400][2];

int main()
{
  scanf("%" SCNi64 "%" SCNi64, &n, &kk);
  int digit_cnt = 0;
  while (n > 0)
  {
    digit[digit_cnt++] = n % 10;
    n /= 10;
  }

  dp[0][0][200][0] = 1;
  for (int i = 0; i < digit_cnt + 4; i++)
    for (int j = 0; j < 1000; j++)
      for (int k = 0; k < 400; k++)
        for (int t = 0; t < 2; t++)
          if (dp[i][j][k][t])
            for (int c = 0; c < 10; c++)
              dp[i + 1][(c * kk + j) / 10][k + c - (c * kk + j) % 10][c == digit[i] ? t : (c > digit[i])] += dp[i][j][k][t];

  int64_t ans = 0;
  for (int i = 0; i < 1000; i++)
    ans += dp[digit_cnt + 4][i][200][0];
  ans -= 1;

  std::cout << ans << std::endl;

  return 0;
}
