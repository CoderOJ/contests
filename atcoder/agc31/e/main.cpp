#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <queue>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

class MinCostFlow
{
private:
  const int n;
  std::vector<std::tuple<int, long long, int>> e;
  std::vector<std::vector<int>> g;
  std::vector<long long> h, dis;
  std::vector<int> pre;
  bool dijkstra(int s, int t)
  {
    dis.assign(n, 1E18);
    pre.assign(n, -1);
    std::priority_queue<std::pair<long long, int>> que;
    dis[s] = 0;
    que.emplace(0, s);
    while (!que.empty())
    {
      auto [d, u] = que.top();
      d = -d;
      que.pop();
      if (dis[u] != d)
        continue;
      for (int i : g[u])
      {
        auto [v, f, c] = e[i];
        if (c > 0 && dis[v] > d + h[u] - h[v] + f)
        {
          dis[v] = d + h[u] - h[v] + f;
          pre[v] = i;
          que.emplace(-dis[v], v);
        }
      }
    }
    return dis[t] != static_cast<long long>(1e18);
  }

public:
  MinCostFlow(int n) : n(n), g(n)
  {
  }
  void addEdge(int u, int v, long long f, int c)
  {
    g[u].push_back((int)e.size());
    e.emplace_back(v, f, c);
    g[v].push_back((int)e.size());
    e.emplace_back(u, -f, 0);
  }
  std::pair<int, long long> minCostMaxFlow(const int s, const int t)
  {
    int flow = 0;
    long long cost = 0;
    h.assign(n, 0);
    while (dijkstra(s, t))
    {
      for (int i = 0; i < n; ++i)
        h[i] += dis[i];
      for (int i = t; i != s; i = get<0>(e[pre[i] ^ 1]))
      {
        --get<2>(e[pre[i]]);
        ++get<2>(e[pre[i] ^ 1]);
      }
      ++flow;
      cost += h[t];
    }
    return {flow, cost};
  }
};

int main()
{
  int n = sc.next_int();
  std::vector<int> x(n), y(n);
  std::vector<long long> v(n);
  for (int i = 0; i < n; ++i)
  {
    x[i] = sc.next_int();
    y[i] = sc.next_int();
    v[i] = sc.next_long();
  }

  int m = sc.next_int();
  std::vector<int> l(n, 1), r(n, 100), d(n, 1), u(n, 100);
  for (int i = 0; i < m; ++i)
  {
    char t = sc.next_char();
    int a = sc.next_int(), b = sc.next_int();
    if (t == 'L')
      l[b] = std::max(l[b], a + 1);
    else if (t == 'R')
      r[b] = std::min(r[b], a - 1);
    else if (t == 'D')
      d[b] = std::max(d[b], a + 1);
    else
      u[b] = std::min(u[b], a - 1);
  }

  for (int i = 1; i < n; ++i)
  {
    l[i] = std::max(l[i], l[i - 1]);
    r[i] = std::min(r[i], r[i - 1]);
    d[i] = std::max(d[i], d[i - 1]);
    u[i] = std::min(u[i], u[i - 1]);
  }
  long long ans = 0;
  for (int k = 1; k <= n; ++k)
  {
    MinCostFlow flow(2 * (n + k + 1));
    const int s = 2 * (n + k), t = s + 1;
    for (int i = 0; i < n; ++i)
      flow.addEdge(i, i + n, (long long)1E15 - v[i], 1);
    for (int i = 0; i < k; ++i)
    {
      flow.addEdge(s, i + 2 * n, 0, 1);
      flow.addEdge(i + 2 * n + k, t, 0, 1);
      for (int j = 0; j < n; ++j)
      {
        if (l[i] <= x[j] && x[j] <= r[k - i - 1])
          flow.addEdge(i + 2 * n, j, 0, 1);
        if (d[i] <= y[j] && y[j] <= u[k - i - 1])
          flow.addEdge(j + n, i + 2 * n + k, 0, 1);
      }
    }
    auto f = flow.minCostMaxFlow(s, t);
    if (f.first != k)
      break;
    ans = std::max(ans, k * (long long)1E15 - f.second);
  }
  std::cout << ans << std::endl;

  return 0;
}
