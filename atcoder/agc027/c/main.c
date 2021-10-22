#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 200005

struct edge_t
{
  struct edge_t *next;
  int v;
};

struct edge_t _ep[N * 2], *e[N], *ep_top = _ep;

void add_edge(int u, int v)
{
  ep_top->next = e[u];
  ep_top->v = v;
  e[u] = ep_top++;
  ep_top->next = e[v];
  ep_top->v = u;
  e[v] = ep_top++;
}

int n, m;
char c[N];
int deg[N][2];

int main()
{
  scanf("%d%d", &n, &m);
  scanf("%s", c + 1);
  for (int i = 0; i < m; i++)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    add_edge(u, v);
  }

  for (int u = 1; u <= n; u++)
    for (struct edge_t *i = e[u]; i; i = i->next)
      deg[u][c[i->v] - 'A']++;

  static int que[N];
  static bool inque[N];
  memset(inque, false, sizeof(inque));
  int *que_front = que, *que_back = que;
  for (int u = 1; u <= n; u++)
    if (deg[u][0] == 0 || deg[u][1] == 0)
      *que_back++ = u, inque[u] = true;

  while (que_front != que_back)
  {
    int u = *que_front++; 
    for (struct edge_t *i = e[u]; i; i = i->next)
    {
      deg[i->v][c[u] - 'A']--;
      if (!inque[i->v] && deg[i->v][c[u] - 'A'] == 0)
        *que_back++ = i->v, inque[i->v] = true;
    }
  }

  puts(que_back - que == n ? "No" : "Yes");

  return 0;
}
