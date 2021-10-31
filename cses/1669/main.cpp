#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#include <queue>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<std::vector<int>> e(n + 1);
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int(), v = sc.next_int();
    e[u].push_back(v);
    e[v].push_back(u);
  }

  std::vector<bool> vis(n + 1);
  std::vector<int> res;

  auto dfs = [&](auto &&self, int u, int f) -> bool {
    if (vis[u])
    {
      res.push_back(u);
      return true;
    }
    vis[u] = true;
    for (int v : e[u])
      if (v != f)
        if (self(self, v, u))
        {
          res.push_back(u);
          return true;
        }
    return false;
  };

  for (int i = 1; i <= n; i++)
    if (!vis[i])
      if (dfs(dfs, i, 0))
        break;

  if (res.empty())
    puts("IMPOSSIBLE");
  else
  {
    while (res.back() != res[0])
      res.pop_back();
    std::cout << res.size() << std::endl;
    for (int x : res)
      std::cout << x << " ";
  }

  return 0;
}
