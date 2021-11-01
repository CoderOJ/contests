#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <functional>
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
  std::vector<int> degree(n);
  std::vector<std::vector<int>> e(n);
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u].emplace_back(v);
  }

  std::vector<bool> vis(n), in_stack(n);
  std::vector<int> pre(n);

  std::function<void(int)> dfs = [&](int u) {
    vis[u] = true;
    in_stack[u] = true;
    for (int v : e[u])
    {
      if (!vis[v])
      {
        pre[v] = u;
        dfs(v);
      }
      else if (in_stack[v])
      {
        pre[v] = u;
        throw v;
      }
    }
    in_stack[u] = false;
  };

  for (int i = 0; i < n; i++)
    if (!vis[i])
    {
      try
      {
        dfs(i);
      }
      catch (int p)
      {
        std::vector<int> ans;
        for (int u = p; ; u = pre[u])
        {
          ans.push_back(u);
          if (pre[u] == p)
            break;
        }
        ans.push_back(p);

        std::cout << ans.size() << std::endl;
        std::reverse(ans.begin(), ans.end());
        for (int x : ans)
          std::cout << x + 1 << " ";
        return 0;
      }
    }

  puts("IMPOSSIBLE");

  return 0;
}
