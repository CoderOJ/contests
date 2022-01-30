#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstring>
#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int INF = 1e9;
constexpr int V   = 105;
constexpr int E   = 1000005;

int dis[V], flow[V], pre[V], deg[V];
int n, m, s, t, ans;

struct list_t
{
  int first[V], next[E], to[E], val[E], flow[E], cost[E];
  int tot;

  list_t()
  {
    memset(first, -1, sizeof(first));
  }
  void insert(int u, int v, int w, int c)
  {
    next[tot] = first[u];
    to[tot]   = v;
    val[tot]  = w;
    cost[tot] = c;
    first[u]  = tot;
    tot       = tot + 1;
  }
  void link(int u, int v, int w, int c)
  {
    insert(u, v, w, c);
    insert(v, u, 0, -c);
  }
} e;

bool inq[V];

bool spfa()
{
  memset(dis, 60, sizeof(dis));
  dis[s]  = 0;
  flow[s] = INF;

  std::queue<int> que;
  for (que.push(s); !que.empty(); que.pop())
  {
    int u = que.front();
    for (int i = e.first[u]; ~i; i = e.next[i])
    {
      int v = e.to[i], w = e.val[i], f = e.flow[i], c = e.cost[i];
      if (dis[v] > dis[u] + c && w > f)
      {
        dis[v]  = dis[u] + c;
        pre[v]  = i;
        flow[v] = std::min(flow[u], w - f);
        if (!inq[v])
        {
          inq[v] = true;
          que.push(v);
        }
      }
    }
    inq[u] = false;
  }
  return dis[t] < INF;
}

void ek()
{
  ans += flow[t] * dis[t];
  for (int u = t; u != s; u = e.to[pre[u] ^ 1])
  {
    e.flow[pre[u]] += flow[t];
    e.flow[pre[u] ^ 1] -= flow[t];
  }
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  
  s = 0;
  t = n + 1;

  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    int w = sc.next_int();
    int f = sc.next_int();

    if (w > f)
    {
      e.link(u, v, INF, 2);
      e.link(u, v, w - f, 1);
      e.link(v, u, f, 1);
      deg[u] -= f;
      deg[v] += f;
    }
    else
    {
      e.link(u, v, INF, 2);
      e.link(u, v, f - w, 0);
      e.link(v, u, w, 1);
      deg[u] -= w;
      deg[v] += w;
      ans += f - w;
    }
  }

  for (int u = 1; u <= n; u++)
  {
    if (deg[u] > 0)
      e.link(s, u, deg[u], 0);
    if (deg[u] < 0)
      e.link(u, t, -deg[u], 0);
  }

  e.link(n, 1, INF, 0);
  while (spfa())
    ek();

  printf("%d\n", ans);
  return 0;
}
