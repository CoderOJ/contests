#include <stdio.h>

#define N 1005
int a[N][N];
char s[N][N];

int main()
{
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++)
  {
    scanf("%s", s[i]);
    for (int j = 0; j < n; j++)
      a[i][j + 1] = a[i][j] + (s[i][j] == '*' ? 1 : 0);
  }

  for (int i = 0; i < q; i++)
  {
    int opt;
    scanf("%d", &opt);
    if (opt == 1)
    {
      int x, y;
      scanf("%d%d", &x, &y);
      x--, y--;

      if (s[x][y] == '.')
      {
        for (int j = y + 1; j <= n; j++)
          a[x][j]++;
        s[x][y] = '*';
      }
      else
      {
        for (int j = y + 1; j <= n; j++)
          a[x][j]--;
        s[x][y] = '.';
      }
    }
    else
    {
      int ux, uy;
      scanf("%d%d", &ux, &uy);
      ux--, uy--;
      int vx, vy;
      scanf("%d%d", &vx, &vy);

      int ans = 0;
      for (int i = ux; i < vx; i++)
        ans += a[i][vy] - a[i][uy];
      printf("%d\n", ans);
    }
  }

  return 0;
}
