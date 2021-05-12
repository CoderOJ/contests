#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define inf 0x3f3f3f3f


#define N 10005
#define M 6 * N

struct edge_t
{
  struct edge_t *next;
  int v, w;
};

struct edge_t *e[N], *en[N], ep[M], *ep_top = ep;
void add_edge(int u, int v, int w) 
{
  ep_top->v    = v;
  ep_top->w    = w;
  ep_top->next = e[u];
  e[u] = ep_top++;
  ep_top->v    = u;
  ep_top->w    = 0;
  ep_top->next = e[v];
  e[v] = ep_top++;
}

struct edge_t *get_rev_edge(struct edge_t *p)
{
  return ep + ((p - ep) ^ 1);
}

int S, T, id_spr = 2;
int dep[N];

bool bfs()
{
  memset(dep, -1, sizeof(*dep) * (size_t)(id_spr));
  dep[S] = 0;
  static int que[N];
  int *que_front = que, *que_back = que;
  *que_back++ = S;
  while (que_front != que_back)
  {
    int u = *que_front++;
    for (struct edge_t *i = e[u]; i; i = i->next)
    {
      if (i->w == 0 || dep[i->v] != -1) continue;
      dep[i->v] = dep[u] + 1;
      *que_back++ = i->v;
    }
  }
  return dep[T] != -1;
}

int min(int a, int b)
{
  return a < b ? a : b;
}

int dfs(int u, int limit)
{
  if (u == T || limit == 0)
    return limit;
  int remain = limit;
  for (struct edge_t **i = &en[u]; *i; *i = (*i)->next)
    if ((*i)->w && dep[(*i)->v] == dep[u] + 1)
    {
      int v_limit = min(remain, (*i)->w);
      int v_w = dfs((*i)->v, v_limit);
      remain -=  v_w;
      (*i)->w -= v_w;
      get_rev_edge(*i)->w += v_w;
    }
  return limit - remain;
}

int dinic()
{
  int ans = 0;
  while (bfs())
  {
    memcpy(en, e, sizeof(*en) * (size_t)id_spr);
    int cur = 0;
    while ((cur = dfs(S, inf)))
      ans += cur;
  }
  return ans;
}

int n, m;
int a[105][105], id[105][105];

int main()
{
  scanf("%d%d", &n, &m);
  for (int i=0; i<n; ++i)
    for (int j=0; j<m; ++j)
      scanf("%d", &a[i][j]);

  S = 0, T = 1;
  for (int i=0; i<n; ++i)
    for (int j=0; j<m; ++j)
    {
      id[i][j] = id_spr++;
      if ((i + j) % 2 == 0)
        add_edge(S, id[i][j], a[i][j]);
      else
        add_edge(id[i][j], T, a[i][j]);
    }

  for (int i=0; i<n; ++i)
    for (int j=0; j<m; ++j)
      if ((i + j) % 2 == 0)
      {
        if (i)       add_edge(id[i][j], id[i-1][j], inf);
        if (j)       add_edge(id[i][j], id[i][j-1], inf);
        if (i+1 < n) add_edge(id[i][j], id[i+1][j], inf);
        if (j+1 < m) add_edge(id[i][j], id[i][j+1], inf);
      }

  int ans = -dinic();
  for (int i=0; i<n; ++i)
    for (int j=0; j<m; ++j)
      ans += a[i][j];

  printf("%d\n", ans);

  return 0;
}
