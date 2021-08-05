#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void swapd(int *x, int *y)
{
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

int imind(int x, int y)
{
  return x < y ? x : y;
}

#define B 20
#define N 100005
#define M 705
#define inf 0x3f3f3f3f

struct edge_t
{
  int v, w;
  struct edge_t *next;
};

struct edge_t edge_pool[N * 2 + M * M * 2 + M * 5];
struct edge_t *tree[N], *edge_tp = edge_pool;
struct edge_t *get_rev_edge(struct edge_t *p)
{
  return edge_pool + ((p - edge_pool) ^ 1);
}
void tree_add_edge(int u, int v)
{
  edge_tp->v = v;
  edge_tp->next = tree[u];
  tree[u] = edge_tp++;
  edge_tp->v = u;
  edge_tp->next = tree[v];
  tree[v] = edge_tp++;
}

struct path_t
{
  int u, v, w;
};
struct path_t p1[N], p2[N];
int n, m1, m2;

int dep[N], fa[N][B];
int dfnl[N], dfnr[N], dfn_top;
void dfs_init(int u, int f)
{
  dfnl[u] = dfn_top++;
  dep[u] = dep[f] + 1;
  fa[u][0] = f;
  for (int i = 0; i + 1 < B; i++)
    fa[u][i + 1] = fa[fa[u][i]][i];
  for (struct edge_t *i = tree[u]; i; i = i->next)
    if (i->v != f) dfs_init(i->v, u);
  dfnr[u] = dfn_top;
}
int lca(int u, int v)
{
  if (dep[u] < dep[v])
    return lca(v, u);
  int d = dep[u] - dep[v];
  for (int i = 0; i < B; i++)
    if (d & (1 << i))
      u = fa[u][i];
  for (int i = B-1; i >= 0; i--)
    if (fa[u][i] != fa[v][i])
    {
      u = fa[u][i];
      v = fa[v][i];
    }
  return u == v ? u : fa[u][0];
}
bool is_anc(int u, int c)
{
  return dfnl[u] <= dfnl[c] && dfnl[c] < dfnr[u];
}
bool is_cross(int u1, int v1, int u2, int v2)
{
  int l1 = lca(u1, v1), l2 = lca(u2, v2);
  if (dep[l1] > dep[l2])
  {
    swapd(&l1, &l2);
    swapd(&u1, &u2);
    swapd(&v1, &v2);
  }
  if (!is_anc(l1, l2))
    return false;
  if (is_anc(l2, u1) || is_anc(l2, v1))
    return true;
  return false;
}

int s, t;
struct edge_t *flow[M * 2], *cur[M * 2];
void flow_add_edge(int u, int v, int w)
{
  // printf("flow_add_edge: %d %d %d\n", u, v, w);
  edge_tp->v = v;
  edge_tp->w = w;
  edge_tp->next = flow[u];
  flow[u] = edge_tp++;
  edge_tp->v = u;
  edge_tp->w = 0;
  edge_tp->next = flow[v];
  flow[v] = edge_tp++;
}

int d[M * 2];
bool bfs()
{
  memset(d, 0x3f, sizeof(d));
  d[s] = 0;
  static int queue[M * 2];
  int *que_front = queue, *que_back = queue;
  *que_back++ = s;
  while (que_front != que_back)
  {
    int u = *que_front++;
    if (u == t) 
      return true;
    for (struct edge_t *i = flow[u]; i; i = i->next)
      if (i->w != 0 && d[i->v] == 0x3f3f3f3f)
      {
        d[i->v] = d[u] + 1;
        *que_back++ = i->v;
      }
  }
  return false;
}
int dfs(int u, int limit)
{
  // printf("dfs u = %d, limit = %d\n", u, limit);
  if (u == t || limit == 0)
    return limit;
  int remain = limit;
  for (struct edge_t **i = &cur[u]; *i; *i = (*i)->next)
    if ((*i)->w && d[(*i)->v] == d[u] + 1)
    {
      int v_limit = imind(remain, (*i)->w);
      int v_cost = dfs((*i)->v, v_limit);
      remain -= v_cost;
      (*i)->w -= v_cost;
      get_rev_edge(*i)->w += v_cost;
    }
  return limit - remain;
}

int dinic()
{
  int ans = 0;
  while (bfs())
  {
    memcpy(cur, flow, sizeof(cur));
    int cur_ans;
    while ((cur_ans = dfs(s, inf)))
      ans += cur_ans;
  }
  return ans;
}

int main()
{
  scanf("%d%d%d", &n, &m1, &m2);  
  for (int i = 1; i < n; i++)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    tree_add_edge(u, v);
  }
  dfs_init(1, 0);

  s = m1 + m2;
  t = s + 1;
  for (int i = 0; i < m1; i++)
  {
    scanf("%d%d%d", &p1[i].u, &p1[i].v, &p1[i].w);
    flow_add_edge(s, i, p1[i].w);
  }
  for (int i = 0; i < m2; i++)
  {
    scanf("%d%d%d", &p2[i].u, &p2[i].v, &p2[i].w);
    flow_add_edge(m1 + i, t, p2[i].w);
  }
  for (int i = 0; i < m1; i++)
    for (int j = 0; j < m2; j++)
      if (is_cross(p1[i].u, p1[i].v, p2[j].u, p2[j].v))
        flow_add_edge(i, m1 + j, inf);

  int ans = 0;
  for (int i = 0; i < m1; i++)
    ans += p1[i].w;
  for (int i = 0; i < m2; i++)
    ans += p2[i].w;
  ans -= dinic();
  printf("%d\n", ans);

  return 0;
}
