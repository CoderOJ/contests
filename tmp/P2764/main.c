#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 350
#define M 15000

struct edge_t 
{
  struct edge_t *next;
  int v, w;
};

struct edge_t e_pool[M], *ep_top = e_pool;
struct edge_t *e[N], *e_f[N];
struct edge_t *get_rev_edge(struct edge_t *p)
{
  return e_pool + ((long)(p - e_pool) ^ 1);
}

void add_edge(int u, int v, int w)
{
  ep_top->v    = v;
  ep_top->w    = w;
  ep_top->next = e[u];
  e[u]         = ep_top++;
  ep_top->v    = u;
  ep_top->w    = 0;
  ep_top->next = e[v];
  e[v]         = ep_top++;
}

int dep[N], s, t, un, n, m;

bool bfs()
{
  memset(dep, -1, sizeof(*dep) * un);
  dep[s] = 0;
  static int que[N];
  int *que_front=que, *que_back=que_front;
  *que_back++ = s;
  while (que_front != que_back)
  {
    int u = *que_front++;
    for (struct edge_t *i = e[u]; i; i = i->next)
      if (i->w != 0 && dep[i->v] == -1) 
      {
        dep[i->v] = dep[u] + 1;
        *que_back++ = i->v;
      }
  }
  return dep[t] != -1;
}

int min(int a, int b)
{
  return a < b ? a : b;
}

int dfs(int u, int limit)
{
  if (u == t) return limit;
  if (limit == 0) return 0;
  
  int remain = limit;
  for (struct edge_t **i = &e_f[u]; *i && remain; *i = (*i)->next)
    if ((*i)->w != 0 && dep[(*i)->v] == dep[u] + 1)
    {
      int v_limit = min(remain, (*i)->w);
      int cur = dfs((*i)->v, v_limit);
      remain -= cur;
      (*i)->w -= cur;
      get_rev_edge(*i)->w += cur;
    }

  return limit - remain;
}

void dinic()
{
  while (bfs())
  {
    memcpy(e_f, e, sizeof(*e) * un);
    while (dfs(s, un));
  }
}

bool vis[N];
void find_ans(int u)
{
  printf("%d ", u + 1);
  for (struct edge_t *i = e[u]; i; i = i->next)
    if (i->w == 0 && i->v != s)
      find_ans(i->v - n);
}

int main()
{
  scanf("%d%d", &n, &m);
  s = n + n, t = s + 1, un = t + 1;
  for (int i=0; i<n; ++i)
  {
    add_edge(s, i, 1);
    add_edge(i+n, t, 1);
  }
  for (int i=0; i<m; ++i)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    u--, v--;
    add_edge(u, v+n, 1);
  }

  dinic();
  
  for (int i=0; i<n; ++i) 
    for (struct edge_t *j=e[i]; j; j=j->next)
      if (j->w == 0 && j->v != s)
        vis[j->v - n] = true;

  int tot = 0;
  for (int i=0; i<n; ++i) if (!vis[i])
  {
    find_ans(i);
    puts("");
    tot++;
  }

  printf("%d\n", tot);
  return 0;
}
