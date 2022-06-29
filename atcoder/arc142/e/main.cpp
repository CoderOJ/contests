#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <limits>
#include <list>
#include <queue>
#include <utility>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

template <class flow_t>
struct mc_flow
{
  struct edge_t
  {
    int     v;
    flow_t  w;
    edge_t *rev;
  };

  using graph_t = std::vector<std::list<edge_t>>;

  static void add_edge(graph_t &e, int u, int v, flow_t w)
  {
    e[u].push_back({v, w, nullptr});
    e[v].push_back({u, 0, nullptr});
    e[u].back().rev = &e[v].back();
    e[v].back().rev = &e[u].back();
  }

  static flow_t dinic(graph_t &e, int s, int t)
  {
    flow_t ans = 0;

    while (true)
    {
      auto dep = [&]() -> std::vector<int> {
        std::vector<int> dep(e.size(), -1);
        dep[s] = 0;

        std::queue<int> que;
        que.push(s);

        while (!que.empty())
        {
          int u = que.front();
          que.pop();
          for (auto &p : e[u])
            if (p.w > 0 && dep[p.v] == -1)
            {
              dep[p.v] = dep[u] + 1;
              que.push(p.v);

              if (p.v == t)
                return dep;
            }
        }

        return {};
      }();

      if (dep.empty())
        break;

      std::vector<typename std::list<edge_t>::iterator> ec(e.size());
      for (size_t i = 0; i < e.size(); i++)
        ec[i] = e[i].begin();

      ans += cm::y_combinate([&](auto &&f, int u, flow_t lim) -> flow_t {
        if (u == t)
          return lim;

        flow_t rem = lim;
        for (auto p = ec[u]; p != e[u].end(); p++)
          if (p->w && dep[u] + 1 == dep[p->v])
          {
            flow_t v_flow = f(p->v, std::min(rem, p->w));
            rem -= v_flow;
            p->w -= v_flow;
            p->rev->w += v_flow;

            if (rem == 0)
              break;
          }

        return lim - rem;
      })(s, std::numeric_limits<flow_t>::max());
    }

    return ans;
  }
};

int main()
{
  int n = sc.next_int();

  std::vector<std::pair<int, int>> a(n);
  for (auto &[x, y] : a)
  {
    x = sc.next_int();
    y = sc.next_int();
  }

  int m = sc.next_int();

  std::vector<std::pair<int, int>> c(m);
  for (auto &[x, y] : c)
  {
    x = sc.next_int() - 1;
    y = sc.next_int() - 1;
  }

  int ans = 0;
  for (const auto &[x, y] : c)
  {
    int lim = std::min(a[x].second, a[y].second);

    if (a[x].first < lim)
    {
      ans += lim - a[x].first;
      a[x].first = lim;
    }

    if (a[y].first < lim)
    {
      ans += lim - a[y].first;
      a[y].first = lim;
    }
  }

  std::vector<int> type(n);
  for (int i = 0; i < n; i++)
    type[i] = (a[i].first < a[i].second) ? 0 : 1;

  c = [&] {
    std::vector<std::pair<int, int>> tc;
    for (const auto &[x, y] : c)
    {
      bool is_ok = (a[x].first >= a[x].second && a[y].first >= a[y].second) ||
                   (a[x].first >= a[y].second && a[y].first >= a[x].second);

      if (!is_ok)
      {
        if (type[x] == 0)
          tc.emplace_back(x, y);
        else
          tc.emplace_back(y, x);
      }
    }
    return tc;
  }();

  see(c);

  using flow = mc_flow<int>;

  cm::counter_t<> cur_u;

  int  s = cur_u();
  int  t = cur_u();
  auto e = [&] {
    std::vector<int>              xs(n);
    std::vector<std::vector<int>> ys(n, std::vector<int>(101));
    for (int i = 0; i < n; i++)
      if (type[i] == 0)
      {
        xs[i] = cur_u();
      }
      else
      {
        for (auto &y : ys[i])
          y = cur_u();
      }

    flow::graph_t e(cur_u.size());

    for (int i = 0; i < n; i++)
      if (type[i] == 0)
      {
        flow::add_edge(e, s, xs[i], a[i].second - a[i].first);
      }
      else
      {
        for (int j = 0; j + 1 <= 100; j++)
          flow::add_edge(
              e, ys[i][j + 1], ys[i][j], std::numeric_limits<int>::max() / 2);
        for (int j = a[i].first + 1; j <= 100; j++)
          flow::add_edge(e, ys[i][j], t, 1);
      }

    for (const auto &[x, y] : c)
      flow::add_edge(
          e, xs[x], ys[y][a[x].second], std::numeric_limits<int>::max() / 2);

    return e;
  }();

  see(ans);
  ans += flow::dinic(e, s, t);
  see(ans);

  std::cout << ans << std::endl;

  return 0;
}
