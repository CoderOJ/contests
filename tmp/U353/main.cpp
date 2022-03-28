#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < n; i++)

const int N = 500005;
int a[N], b[N], n;

void read_arr(int *a, int n)
{
  static char s[N];
  scanf("%s", s);
  rep (i, n)
  {
    char c = s[i];
    if (c == 'R') a[i] = 0;
    else if (c == 'G') a[i] = 1;
    else a[i] = 2;
  }
}

int dp[N][3][3];

int dis(int a0, int a1, int b0, int b1)
{
  if (a0 == b0 && a1 == b1)
    return 0;
  else if ((a0 == a1) != (b0 == b1))
    return (a0 == b0 || a0 == b1 || a1 == b0 || a1 == b1) ? 0x1f1f1f1f : 1;
  else 
    return 0x1f1f1f1f;
}

int main()
{
  scanf("%d", &n);
  read_arr(a, n);
  read_arr(b, n);
  memset(dp, 0x3f, sizeof(dp));
  rep (i, 3) dp[0][i][i] = 0;
  rep (i, n - 1) rep (a1, 3) rep (b0, 3) rep (b1, 3) rep (c0, 3) rep (d1, 3)
    dp[i + 1][a1][d1] = std::min(dp[i + 1][a1][d1], dis(a[i], a1, b0, b1) + dp[i][b0][c0] + dis(c0, b1, b[i], d1));
  printf("%d\n", dp[n - 1][a[n - 1]][b[n - 1]]);
  return 0;
}
