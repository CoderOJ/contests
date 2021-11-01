#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <limits>
#include <queue>
#include <utility>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  int k = sc.next_int();

  std::vector<std::vector<std::pair<int, int>>> e(n);
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    int w = sc.next_int();
    e[u].emplace_back(v, w);
  }

  std::vector<int> pop_cnt(n, 0);
  std::vector<std::vector<long long>> dis(
      n, std::vector<long long>(k, std::numeric_limits<long long>::max()));
  dis[0][0] = 0;
  std::priority_queue<std::pair<long long, int>,
                      std::vector<std::pair<long long, int>>,
                      std::greater<std::pair<long long, int>>>
      que;
  que.emplace(0, 0);

  while (!que.empty())
  {
    const auto [d, u] = que.top();
    see(d, u);
    que.pop();
    if (++pop_cnt[u] > k)
      continue;
    for (const auto &[v, w] : e[u])
      if (d + w < dis[v].back())
      {
        auto it = --dis[v].end();
        while (it != dis[v].begin() && d + w < *(it - 1))
          it--;
        dis[v].insert(it, d + w);
        dis[v].pop_back();
        que.emplace(d + w, v);
      }
  }

  for (long long x : dis[n - 1])
    std::cout << x << " ";

  return 0;
}
