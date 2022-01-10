#include <stdbool.h>
#include <stdio.h>

#define N 205
#define INF 0x3f3f3f3f

int  e[N][N];
char s[N];
int  n;

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    scanf("%s", s);
    for (int j = 0; j < n; j++)
      e[i][j] = s[j] == '0' ? INF : 1;
    e[i][i] = 0;
  }

  for (int r = 0; r < n; r++)
    for (int u = 0; u < n; u++)
      for (int v = 0; v < n; v++)
        if (e[u][r] + e[r][v] < e[u][v])
          e[u][v] = e[u][r] + e[r][v];

  int ans = -1;
  for (int s = 0; s < n; s++)
  {
    int cur_diameter = 0;
    for (int u = 0; u < n; u++)
      if (e[s][u] > cur_diameter)
        cur_diameter = e[s][u];

    bool is_bipart = false;
    for (int u = 0; u < n; u++)
      for (int v = 0; v < n; v++)
        if (e[u][v] == 1)
          if (e[s][u] == e[s][v])
          {
            is_bipart = true;
            break;
          }

    if (!is_bipart)
      if (cur_diameter + 1 > ans)
        ans = cur_diameter + 1;
  }

  printf("%d\n", ans);
  return 0;
}
