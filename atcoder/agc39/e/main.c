#include <stdio.h>

#define N 40

char s[N];
int  e[N][N];
int  n;

long long dp[N][N][N];

int main()
{
  scanf("%d", &n);
  n = n * 2;
  for (int i = 0; i < n; i++)
  {
    scanf("%s", s);
    for (int j = 0; j < n; j++)
      e[i][j] = s[j] - '0';
  }

  for (int i = 1; i < n; i++)
    dp[i][i][i] = 1;

  for (int len = 3; len < n; len += 2)
    for (int left = 1, right = left + len - 1; right < n; left++, right++)
      for (int center = left + 1; center < right; center++)
        for (int lcenter = left; lcenter < center; lcenter++)
          for (int rcenter = right; rcenter > center; rcenter--)
            if (e[lcenter][rcenter])
              for (int lmid = lcenter; lmid < center; lmid++)
                if (dp[left][lmid][lcenter])
                  for (int rmid = rcenter; rmid > center; rmid--)
                    if (dp[rmid][right][rcenter])
                      dp[left][right][center] += dp[left][lmid][lcenter] *
                                                 dp[rmid][right][rcenter] *
                                                 dp[lmid + 1][rmid - 1][center];

  long long ans = 0;
  for (int i = 1; i < n; i++)
    if (e[0][i])
      ans += dp[1][n - 1][i];
  printf("%lld\n", ans);

  return 0;
}
