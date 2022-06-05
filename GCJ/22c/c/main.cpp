#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    printf("Case #%d: ", i + 1);

    int n = sc.next_int();

    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int() - 1;
    for (int i = 0; i < n; i++)
      b[i] = sc.next_int() - 1;

    std::vector<std::vector<int>> e(n);

    auto add_edge = [&](int u, int v) {
      e[u].push_back(v);
      e[v].push_back(u);
    };
    for (int i = 0; i < n; i++)
    {
      add_edge(i, a[i]);
      add_edge(i, b[i]);
      add_edge(i, a[a[i]]);
      add_edge(i, a[b[i]]);
      add_edge(i, b[a[i]]);
      add_edge(i, b[b[i]]);
    }

    bool invalid = [&] {
      for (int u = 0; u < n; u++)
        if (std::find(e[u].begin(), e[u].end(), u) != e[u].end())
          return true;
      return false;
    }();

    if (invalid)
    {
      puts("IMPOSSIBLE");
    }
    else
    {
      auto mex = [](const std::vector<int> &a) {
        for (int i = 0;; i++)
          if (std::find(a.begin(), a.end(), i) == a.end())
            return i;
      };

      std::vector<int> deg(n);
      for (int i = 0; i < n; i++)
        deg[i] = static_cast<int>(e[i].size());

      std::queue<int>   que;
      std::vector<bool> vis(n, false);
      for (int u = 0; u < n; u++)
        if (deg[u] <= 12)
        {
          que.push(u);
          vis[u] = true;
        }

      std::vector<int> order;
      while (!que.empty())
      {
        int u = que.front();
        que.pop();
        order.push_back(u);
        for (int v : e[u])
          if (!vis[v])
          {
            deg[v] -= 1;
            if (deg[v] <= 12)
            {
              que.push(v);
              vis[v] = true;
            }
          }
      }

      std::reverse(order.begin(), order.end());
      std::vector<int> col(n, -1);
      for (int u : order)
      {
        std::vector<int> adj;
        for (int v : e[u])
          if (col[v] != -1)
            adj.push_back(col[v]);
        col[u] = mex(adj);
      }

      const char *alpha = "ACDEHIJKMORST";
      for (int u = 0; u < n; u++)
        putchar_unlocked(alpha[col[u]]);
      puts("");
    }
  }
  return 0;
}
