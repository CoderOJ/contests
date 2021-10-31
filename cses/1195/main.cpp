#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <limits>
#include <queue>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
#define int long long

  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<std::vector<std::pair<int, int>>> e(n * 2);
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1, v = sc.next_int() - 1, w = sc.next_int();
    e[u].emplace_back(v, w);
    e[u].emplace_back(v + n, w / 2);
    e[u + n].emplace_back(v + n, w);
  }

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      que;
  std::vector<int> dis(n * 2, std::numeric_limits<int>::max());
  que.emplace(dis[0] = 0, 0);
  while (!que.empty())
  {
    const auto [d, u] = que.top();
    que.pop();
    if (dis[u] != d)
      continue;
    for (const auto &[v, w] : e[u])
      if (check_min(dis[v], d + w))
        que.emplace(dis[v], v);
  }

  printf("%lld\n", dis[n * 2 - 1]);

  return 0;
}
