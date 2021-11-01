#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <cstring>
#include <queue>
#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 100005;
constexpr int M = 200005;

struct edge_t
{
  struct edge_t *next;
  int v, w;
};

struct edge_t _ep[M * 4], *ep = _ep, *e[N * 2], *ef[N * 2];

struct edge_t *get_rev_edge(struct edge_t *p)
{
  return _ep + ((p - _ep) ^ 1);
}

void add_edge(int u, int v, int w)
{
  see(u, v, w);
  ep->v = v;
  ep->w = w;
  ep->next = e[u];
  e[u] = ep++;
  ep->v = u;
  ep->w = 0;
  ep->next = e[v];
  e[v] = ep++;
}

int dep[N * 2];
bool bfs(int s, int t)
{
  memset(dep, 0x3f, sizeof(dep));
  dep[s] = 0;
  std::queue<int> que;
  que.push(s);
  while (!que.empty())
  {
    int u = que.front();
    que.pop();
    if (u == t)
      break;
    for (struct edge_t *i = e[u]; i; i = i->next)
      if (i->w)
        if (check_min(dep[i->v], dep[u] + 1))
          que.push(i->v);
  }
  return dep[t] != 0x3f3f3f3f;
}

int dfs(int u, int limit, int t)
{
  if (u == t || limit == 0)
    return limit;
  int remain = limit;
  for (struct edge_t *&i = ef[u]; i && remain; i = i->next)
    if (dep[u] + 1 == dep[i->v] && i->w)
    {
      int v_limit = std::min(remain, i->w);
      int cur = dfs(i->v, v_limit, t);
      remain -= cur;
      i->w -= cur;
      get_rev_edge(i)->w += cur;
    }
  return limit - remain;
}

int dinic(int s, int t)
{
  int res = 0;
  while (bfs(s, t))
  {
    while (int cur = (memcpy(ef, e, sizeof(e)), dfs(s, 0x3f3f3f3f, t)))
      res += cur;
  }
  return res;
}

int vis[N];
int main()
{
  int n = sc.next_int();
  const int s = 0, t = 1;
  for (int i = 2; i <= n; i++)
    add_edge(s, i, 1);
  for (int i = n + 2; i <= 2 * n; i++)
    add_edge(i, t, 1);
  for (int i = 2; i <= n; i++)
  {
    int c = sc.next_int();
    for (int j = 0; j < c; j++)
    {
      int u = sc.next_int();
      add_edge(i, n + u, 1);
    }
  }

  int ans = dinic(s, t);
  see(ans);
  cm_assert(ans <= n - 1);
  if (ans != n - 1)
  {
    puts("-1");
    return 0;
  }

  std::vector<std::tuple<int, int, int>> es;
  std::queue<int> que;
  que.push(1);
  while (!que.empty())
  {
    int u = que.front();
    see(u);
    que.pop();
    for (struct edge_t *i = e[n + u]; i; i = i->next)
      if (i->v >= 2 && i->v <= n && !vis[i->v])
      {
        see(i->v);
        vis[i->v] = true;
        for (struct edge_t *j = e[i->v]; j; j = j->next)
          if (j->v > n && !j->w)
          {
            es.emplace_back(i->v, u, j->v - n);
            que.push(j->v - n);
          }
      }
  }

  std::sort(es.begin(), es.end());

  if ((int)es.size() != n - 1)
    puts("-1");
  else
    for (const auto &[id, u, v] : es)
      printf("%d %d\n", u, v);

  return 0;
}
