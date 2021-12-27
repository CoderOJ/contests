#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstring>
#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int                                   n;
std::tuple<long long, long long, int> a[1001], b[1001];

namespace mincostmaxflow
{

struct edge_t
{
  int       to, nxt, flow;
  long long cost;
};

int       s, t, e_cur;
int       head[3001], p[5], flow[3001], pre[3001], le[3001];
bool      vis[3001];
edge_t    e[200001];
long long dis[3001], h[3001];

void add_edge(int f, int t, int w, long long c)
{
  e[e_cur] = {t, head[f], w, c};
  head[f]  = e_cur++;
}

void build()
{
  for (int i = 1; i <= 4; i++)
    p[i] = 2 * n + i;
  t = 2 * n + 5;
  std::memset(head, -1, 4 * (t + 1));
  for (int i = 1; i <= n; i++)
  {
    const auto [x, y, c] = a[i];
    add_edge(s, i, c, 0LL), add_edge(i, s, 0, 0LL);
    add_edge(i, p[1], c, x + y), add_edge(p[1], i, 0, -x - y);
    add_edge(i, p[2], c, x - y), add_edge(p[2], i, 0, -x + y);
    add_edge(i, p[3], c, -x + y), add_edge(p[3], i, 0, x - y);
    add_edge(i, p[4], c, -x - y), add_edge(p[4], i, 0, x + y);
  }
  for (int i = 1; i <= n; i++)
  {
    const auto [x, y, c] = b[i];
    add_edge(p[1], n + i, c, -x - y), add_edge(n + i, p[1], 0, x + y);
    add_edge(p[2], n + i, c, -x + y), add_edge(n + i, p[2], 0, x - y);
    add_edge(p[3], n + i, c, x - y), add_edge(n + i, p[3], 0, -x + y);
    add_edge(p[4], n + i, c, x + y), add_edge(n + i, p[4], 0, -x - y);
    add_edge(i + n, t, c, 0LL), add_edge(t, i + n, 0, 0LL);
  }
}

void init()
{
  std::memset(dis + 1, 0x3f, 8 * t);
  std::queue<int> que;
  que.emplace(s);
  vis[s] = true;
  while (!que.empty())
  {
    int u = que.front();
    que.pop(), vis[u] = false;
    for (int i = head[u]; i != -1; i = e[i].nxt)
    {
      if (!e[i].flow)
        continue;
      int v = e[i].to;
      if (dis[u] + e[i].cost < dis[v])
      {
        dis[v] = dis[u] + e[i].cost;
        if (!vis[v])
          que.emplace(v), vis[v] = true;
      }
    }
  }
  std::memcpy(h + 1, dis + 1, 8 * t);
}

bool dijkstra()
{
  std::memset(dis + 1, 0x3f, 8 * t);
  std::priority_queue<std::pair<long long, int>,
                      std::vector<std::pair<long long, int>>,
                      std::greater<std::pair<long long, int>>>
      que;
  que.emplace(0LL, s);
  pre[t]  = -1;
  flow[s] = 0x3f3f3f3f;
  while (!que.empty())
  {
    const auto [d, u] = que.top();
    que.pop();
    if (dis[u] < d)
      continue;
    for (int i = head[u]; i != -1; i = e[i].nxt)
    {
      if (!e[i].flow)
        continue;
      int       v = e[i].to;
      long long w = e[i].cost + h[u] - h[v];
      if (dis[u] + w < dis[v])
      {
        dis[v] = dis[u] + w, pre[v] = u, le[v] = i;
        flow[v] = std::min(flow[u], e[i].flow);
        que.emplace(dis[v], v);
      }
    }
  }
  return pre[t] != -1;
}

long long solve()
{
  init();
  long long ans = 0LL;
  while (dijkstra())
  {
    for (int i = 1; i <= t; i++)
      if (dis[i] != 0x3f3f3f3f3f3f3f3fLL)
        h[i] += dis[i];
    for (int p = t; p != s; p = pre[p])
      e[le[p]].flow -= flow[t], e[le[p] ^ 1].flow += flow[t];
    ans += flow[t] * h[t];
  }
  return ans;
}

} // namespace mincostmaxflow

int main()
{
  n = sc.next_int();
  for (int i = 1; i <= n; i++)
  {
    long long x = sc.next_int();
    long long y = sc.next_int();
    int       c = sc.next_int();
    a[i]        = {x, y, c};
  }
  for (int i = 1; i <= n; i++)
  {
    long long x = sc.next_int();
    long long y = sc.next_int();
    int       c = sc.next_int();
    b[i]        = {x, y, c};
  }

  mincostmaxflow::build();
  std::cout << -mincostmaxflow::solve();

  return 0;
}
