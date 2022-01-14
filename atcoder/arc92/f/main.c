#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define N 1000
#define M 200000

int  uu[M], vv[M];
int  e[N][N];
int *ed[N];
int  n, m;

int from_forward[N][N];
int from_backward[N][N];

void dfs_calc_from(int *from, int u, int col)
{
  from[u] = col;
  for (int *i = e[u]; i != ed[u]; i++)
    if (from[*i] == -1)
      dfs_calc_from(from, *i, col);
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    ed[i] = e[i];
  for (int i = 0; i < m; i++)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    u--, v--;
    uu[i] = u, vv[i] = v;
    *ed[u]++ = v;
  }

  for (int src = 0; src < n; src++)
  {
    memset(from_forward[src], -1, sizeof(from_forward[src]));
    from_forward[src][src] = src;
    for (int *i = e[src]; i != ed[src]; i++)
      if (from_forward[src][*i] == -1)
        dfs_calc_from(from_forward[src], *i, *i);

    memset(from_backward[src], -1, sizeof(from_backward[src]));
    from_backward[src][src] = src;
    for (int *i = ed[src] - 1; i >= e[src]; i--)
      if (from_backward[src][*i] == -1)
        dfs_calc_from(from_backward[src], *i, *i);
  }

  for (int i = 0; i < m; i++)
  {
    int  u = uu[i], v = vv[i];
    bool forawrd_visible  = from_forward[u][v] != from_backward[u][v];
    bool backward_visible = from_forward[v][u] != -1;
    /* printf("%d %d %d %d\n", u, v, from_forward[u][v], from_backward[u][v]);
     */
    puts(backward_visible != forawrd_visible ? "diff" : "same");
  }

  return 0;
}
