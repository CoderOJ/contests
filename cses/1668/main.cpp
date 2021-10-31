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

  std::vector<int> col(n + 1);

  auto dfs = [&](auto &&self, int u, int c) -> void {
    if (col[u] && col[u] != c)
    {
      puts("IMPOSSIBLE");
      exit(0);
    }
    if (col[u])
      return;
    col[u] = c;
    for (int v : e[u])
      self(self, v, 3 - c);
  };

  for (int i = 1; i <= n; i++)
    if (!col[i])
      dfs(dfs, i, 1);
  for (int i = 1; i <= n; i++)
    std::cout << col[i] << " ";

  return 0;
}
