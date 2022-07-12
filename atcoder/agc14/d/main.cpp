#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <queue>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();

  std::vector<std::vector<int>> e(n);
  for (int i = 0; i < n - 1; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  std::vector<int> deg(n, 0);
  for (int u = 0; u < n; u++)
    deg[u] = static_cast<int>(e[u].size());

  std::queue<int> deg1;
  for (int u = 0; u < n; u++)
    if (deg[u] == 1)
      deg1.push(u);

  std::vector<bool> vis(n, false);
  while (!deg1.empty())
  {
    int u = deg1.front();
    deg1.pop();

    if (!vis[u])
    {
      vis[u] = true;

      if (deg[u] == 0)
      {
        puts("First");
        return 0;
      }

      int v = [&] {
        for (int v: e[u])
          if (!vis[v])
            return v;
        return -1;
      }();
      vis[v] = true;

      for (int vv: e[v])
        if (!vis[vv])
        {
          deg[vv] -= 1;
          if (deg[vv] == 1)
            deg1.push(vv);
        }
    }
  }

  puts("Second");
  return 0;
}
