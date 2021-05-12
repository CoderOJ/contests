#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int min(int a, int b)
{
  return a < b ? a : b;
}

#define N 20005
#define M 400005

int n, m;
int u[M], v[M], w[M];

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
  ep_top->w    = w;
  ep_top->next = e[v];
  e[v] = ep_top++;
}

void clear_graph()
{
  memset(e, 0, sizeof(e));
  ep_top = ep;
}

struct edge_t *get_rev_edge(struct edge_t *p)
{
  return ep + ((p - ep) ^ 1);
}

int dep[N];
int s, t, l;

bool bfs()
{
  memset(dep, -1, sizeof(dep));
  dep[s] = 0;

  static int que[N];
  int *que_front = que, *que_back = que;
  *que_back++ = s;

  while (que_front != que_back)
  {
    int u = *que_front++;
    for (struct edge_t *i = e[u]; i; i = i->next)
      if (i->w && dep[i->v] == -1)
      {
        dep[i->v] = dep[u] + 1;
        *que_back++ = i->v;
      }
  }

  return dep[t] != -1;
}

int dfs(int u, int limit)
{
  if (u == t || limit == 0)
    return limit;

  int remain = limit;
  for (struct edge_t **i = &en[u]; *i; *i = (*i)->next)
    if ((*i)->w && dep[(*i)->v] == dep[u] + 1)
    {
      int v_limit = min(remain, (*i)->w);
      int v_w = dfs((*i)->v, v_limit);
      remain -= v_w, (*i)->w -= v_w;
      get_rev_edge(*i)->w += v_w;
    }

  return limit - remain;
}

int dinic()
{
  int ans = 0;
  while (bfs())
  {
    memcpy(en, e, sizeof(e));
    int cur = 0;
    while ((cur = dfs(s, 0x3f3f3f3f)))
      ans += cur;
  }
  return ans;
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i=0; i<m; ++i)
    scanf("%d%d%d", &u[i], &v[i], &w[i]);
  scanf("%d%d%d", &s, &t, &l);

  int ans = 0;

  for (int i=0; i<m; ++i) 
    if (w[i] < l)
      add_edge(u[i], v[i], 1);
  ans += dinic();

  clear_graph();
  for (int i=0; i<m; ++i) 
    if (w[i] > l)
      add_edge(u[i], v[i], 1);
  ans += dinic();

  printf("%d\n", ans);

  return 0;
}
