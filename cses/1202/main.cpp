#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  constexpr int MOD = 1'000'000'007;
  using int_t = cm::intm<MOD>;

  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<std::vector<std::pair<int, int>>> e(n);
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    int w = sc.next_int();
    e[u].emplace_back(v, w);
  }

  std::vector<long long> dis(n, std::numeric_limits<long long>::max() / 2);
  std::vector<int_t> cnt(n, 0);
  std::vector<int> min_edges(n, 0), max_edges(n, 0);
  cnt[0] = 1;
  dis[0] = 0;

  std::priority_queue<std::pair<long long, int>,
                      std::vector<std::pair<long long, int>>,
                      std::greater<std::pair<long long, int>>>
      que;
  que.emplace(0, 0);
  while (!que.empty())
  {
    const auto [d, u] = que.top();
    que.pop();
    if (d != dis[u])
      continue;

    for (const auto &[v, w] : e[u])
    {
      if (d + w < dis[v])
      {
        dis[v] = d + w;
        min_edges[v] = min_edges[u] + 1;
        max_edges[v] = max_edges[u] + 1;
        cnt[v] = cnt[u];
        que.emplace(dis[v], v);
      }
      else if (d + w == dis[v])
      {
        check_min(min_edges[v], min_edges[u] + 1);
        check_max(max_edges[v], max_edges[u] + 1);
        cnt[v] += cnt[u];
      }
    }
  }

  std::cout << dis[n - 1] << " " << cnt[n - 1] << " " << min_edges[n - 1] << " "
            << max_edges[n - 1] << std::endl;

  return 0;
}
