#include <bits/stdc++.h>

const int N = 2005;
const int M = 4005;
const int V = 6005;
const int E = 500005;

struct edge_t
{
  int v, w;
  edge_t *next;
};

edge_t _ep[E], *e[V], *ec[V], *ep = _ep;

edge_t *add_edge(int u, int v, int w)
{
  // printf("edge: %d %d %d\n", u, v, w);
  auto res = ep;
  ep->v = v;
  ep->w = w;
  ep->next = e[u];
  e[u] = ep++;
  ep->v = u;
  ep->w = 0;
  ep->next = e[v];
  e[v] = ep++;
  return res;
}

edge_t *get_rev_edge(edge_t *p)
{
  return _ep + ((p - _ep) ^ 1);
}

int dis[V];
bool bfs(int s, int t)
{
  std::fill(dis, dis + V, -1);
  dis[s] = 0;
  std::queue<int> que;
  que.push(s);
  while (!que.empty())
  {
    int u = que.front();
    que.pop();
    if (u == t) return true;
    for (edge_t *p = e[u]; p; p = p->next)
      if (p->w > 0 && dis[p->v] == -1)
      {
        dis[p->v] = dis[u] + 1;
        que.push(p->v);
      }
  }
  return false;
}

int dfs(int u, int t, int lim)
{
  if (u == t || lim == 0) return lim;
  int remain = lim;
  for (edge_t *&p = ec[u]; p; p = p->next)
    if (p->w > 0 && dis[p->v] == dis[u] + 1)
    {
      int v_lim = std::min(remain, p->w);
      int cur = dfs(p->v, t, v_lim);
      remain -= cur;
      p->w -= cur;
      get_rev_edge(p)->w += cur;
      if (remain == 0) return lim - remain;
    }
  return lim - remain;
}

int dinic(int s, int t, int lim)
{
  int remain = lim;
  while (remain && bfs(s, t))
  {
    int cur;
    do
    {
      std::copy(e, e + V, ec);
      cur = dfs(s, t, remain);
      remain -= cur;
    } while (remain && cur);
  }
  return lim - remain;
}

edge_t *ue[N], *ee[M];
int u_id[N], e_id[M];
int u[M], v[M];
int s, t, cur_u, f;
int n, m;

void reset_w(edge_t *p, int w)
{
  auto q = get_rev_edge(p);

  int dec = q->w;
  // printf("reset_w: dec = %d\n", dec);
  p->w = 0;
  q->w = 0;
  f -= dec;
  dinic(q->v, s, dec);
  dinic(t, p->v, dec);

  p->w = w;
  f += dinic(s, t, 0x3f3f3f3f);
}

int main()
{
  s = cur_u++;
  t = cur_u++;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) 
    u_id[i] = cur_u++;
  for (int i = 0; i < m; i++)
  {
    scanf("%d%d", &u[i], &v[i]);
    e_id[i] = cur_u++;
    if (u[i] == v[i])
    {
      puts("No");
      return 0;
    }
  }

  for (int i = 0; i < m; i++)
    ee[i] = add_edge(s, e_id[i], 1);
  for (int i = 1; i <= n; i++)
    ue[i] = add_edge(u_id[i], t, 2);
  for (int i = 0; i < m; i++)
  {
    add_edge(e_id[i], u_id[u[i]], 0x3f3f3f3f);
    add_edge(e_id[i], u_id[v[i]], 0x3f3f3f3f);
  }
  f = dinic(s, t, 0x3f3f3f3f);
  // printf("f = %d\n", f);

  for (int i = 1; i <= n; i++)
  {
    reset_w(ue[i], 0);
    // printf("f = %d\n", f);
    if (m - f > 0)
    {
      puts("No");
      return 0;
    }
    reset_w(ue[i], 2);
    // printf("f = %d\n", f);
  }
  puts("Yes");

  return 0;
}
