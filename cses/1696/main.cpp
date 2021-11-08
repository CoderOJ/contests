#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <functional>
#include <limits>
#include <list>
#include <queue>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  struct edge_t
  {
    edge_t *rev;
    int v, w;

    edge_t(edge_t *rev, int v, int w) : rev(rev), v(v), w(w)
    {
    }
  };

  int n = sc.next_int();
  int m = sc.next_int();
  int k = sc.next_int();

  const int s = n + m, t = s + 1;
  std::vector<std::list<edge_t>> e(n + m + 2);
  auto add_edge = [&](int u, int v, int w) {
    e[u].emplace_back(nullptr, v, w);
    e[v].emplace_back(nullptr, u, 0);
    e[u].back().rev = &e[v].back();
    e[v].back().rev = &e[u].back();
  };
  for (int i = 0; i < n; i++)
    add_edge(s, i, 1);
  for (int i = 0; i < m; i++)
    add_edge(i + n, t, 1);
  for (int i = 0; i < k; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    add_edge(u, v + n, 1);
  }

  std::vector<int> dep(n + m + 2);
  auto bfs = [&](int s, int t) {
    std::fill(dep.begin(), dep.end(), std::numeric_limits<int>::max());
    dep[s] = 0;
    std::queue<int> que;
    que.push(s);
    while (!que.empty())
    {
      int u = que.front();
      que.pop();
      if (u == t)
        break;
      for (const auto [_, v, w] : e[u])
        if (w > 0)
          if (check_min(dep[v], dep[u] + 1))
            que.push(v);
    }
    return dep[t] != std::numeric_limits<int>::max();
  };

  std::vector<std::list<edge_t>::iterator> ec(n + m + 2);
  std::function<long long(int, int, long long)> dfs =
      [&](int u, int t, long long limit) -> long long {
    if (u == t || limit == 0)
      return limit;
    long long remain = limit;
    for (auto &it = ec[u]; it != e[u].end(); it++)
      if (dep[it->v] == dep[u] + 1)
      {
        long long v_limit = std::min(remain, static_cast<long long>(it->w));
        long long v_cur = dfs(it->v, t, v_limit);
        remain -= v_cur;
        it->w -= v_cur;
        it->rev->w += v_cur;
      }
    return limit - remain;
  };

  long long max_flow = 0;
  while (bfs(s, t))
  {
    while (true)
    {
      for (int i = 0; i < n + m + 2; i++)
        ec[i] = e[i].begin();
      long long cur = dfs(s, t, std::numeric_limits<long long>::max() / 2);
      max_flow += cur;
      if (cur == 0)
        break;
    }
  }

  std::cout << max_flow << std::endl;
  {
    for (int u = 0; u < n; u++)
      for (const auto [_, v, w] : e[u])
        if (v < s && w == 0)
          std::cout << u + 1 << " " << v - n + 1 << std::endl;
  }

  return 0;
}
