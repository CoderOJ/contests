#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define N 105
int a[N][N], b[N][N], c[N][N];
int n, m;

int origin[N][N];

void swap(int *a, int *b)
{
  int t = *a;
  *a    = *b;
  *b    = t;
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
    {
      scanf("%d", &a[i][j]);
      origin[j][(a[i][j] - 1) / m + 1]++;
      b[i][j] = a[i][j];
    }

  for (int timer = 0; timer < n * m; timer++)
    for (int i = 1; i < m; i++)
      for (int j = 1; j <= n; j++)
        if (origin[i][(b[j][i] - 1) / m + 1] > 1)
        {
          origin[i][(b[j][i] - 1) / m + 1]--;
          origin[i][(b[j][i + 1] - 1) / m + 1]++;
          origin[i + 1][(b[j][i] - 1) / m + 1]++;
          origin[i + 1][(b[j][i + 1] - 1) / m + 1]--;
          swap(&b[j][i], &b[j][i + 1]);
        }

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      c[i][j] = b[i][j];
  for (int timer = 0; timer < n; timer++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
      {
        int gu = c[i][j];
        swap(&c[i][j], &c[(gu - 1) / m + 1][j]);
      }

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
      printf("%d ", b[i][j]);
    puts("");
  }
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
      printf("%d ", c[i][j]);
    puts("");
  }

  return 0;
}
