#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstdint>
#include <queue>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 1 << 18, 1 << 8)

std::vector<std::pair<int, int>> e[N];

int64_t t;
int     n, m;
int     a[N];

int64_t dis[N];

void dijkstra(const std::vector<int> &s)
{
  std::fill(dis, dis + N, 0x3f3f3f3f3f3f3f3f);

  using que_t = std::pair<int64_t, int>;
  std::priority_queue<que_t, std::vector<que_t>, std::greater<>> que;
  for (int u : s)
  {
    dis[u] = 0;
    que.emplace(0, u);
  }

  while (!que.empty())
  {
    int64_t d = que.top().first;
    int     u = que.top().second;
    que.pop();
    if (dis[u] < d)
      continue;

    int64_t da = d / m;
    int64_t db = d % m;
    for (auto &[v, w] : e[u])
    {
      int64_t vd = w >= db ? da * m + w : (da + 1) * m + w;
      if (check_min(dis[v], vd))
        que.emplace(vd, v);
    }
  }
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  t = sc.next_long();
  for (int i = 0; i < m; i++)
  {
    int v = sc.next_int() - 1;
    int u = sc.next_int() - 1;
    e[u].emplace_back(v, i);
  }
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  for (int b = 0; b < 8; b++)
  {
    std::vector<int> s;
    for (int i = 0; i < n; i++)
      if (a[i] & (1 << b))
        s.emplace_back(i);
    dijkstra(s);
    for (int i = 0; i < n; i++)
      if (dis[i] < t)
        a[i] |= 1 << b;
  }
  for (int i = 0; i < n; i++)
    std::cout << a[i] << " ";
  return 0;
}
