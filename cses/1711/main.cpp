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
    bool is_rev;

    edge_t(edge_t *rev, int v, int w, bool is_rev) : rev(rev), v(v), w(w), is_rev(is_rev)
    {
    }
  };

  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<std::list<edge_t>> e(n);
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    int w = 1;
    e[u].emplace_back(nullptr, v, w, true);
    e[v].emplace_back(nullptr, u, 0, false);
    e[u].back().rev = &e[v].back();
    e[v].back().rev = &e[u].back();
  }

  std::vector<int> dep(n);
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
      for (const auto [_, v, w, __] : e[u])
        if (w > 0)
          if (check_min(dep[v], dep[u] + 1))
            que.push(v);
    }
    return dep[t] != std::numeric_limits<int>::max();
  };

  std::vector<std::list<edge_t>::iterator> ec(n);
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
  const int s = 0, t = n - 1;
  while (bfs(s, t))
  {
    while (true)
    {
      for (int i = 0; i < n; i++)
        ec[i] = e[i].begin();
      long long cur = dfs(s, t, std::numeric_limits<long long>::max() / 2);
      max_flow += cur;
      if (cur == 0)
        break;
    }
  }

  std::cout << max_flow << std::endl;
  {
    for (int i = 0; i < max_flow; i++)
    {
      std::vector<int> ans;
      std::function<void(int)> dfs = [&](int u) {
        ans.push_back(u);
        if (u == t)
          throw 1;
        for (auto &[_, v, w, is_rev] : e[u])
          if (is_rev && w == 0)
          {
            w = 1;
            dfs(v);
          }
      };
      try
      {
        dfs(s);
      }
      catch (int x)
      {
      }
      std::cout << ans.size() << std::endl;
      for (int x : ans)
        std::cout << x + 1 << " ";
      std::cout << std::endl;
    }
  }

  return 0;
}
