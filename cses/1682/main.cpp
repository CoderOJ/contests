#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstdlib>
#include <functional>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<std::vector<int>> e(n);
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u].push_back(v);
  }

  std::vector<int> dfn(n, -1);
  std::vector<int> low(n, -1);
  int cur_dfn = 0;

  std::function<void(int, int)> dfs = [&](int u, int from) {
    low[u] = dfn[u] = cur_dfn++;
    for (int v : e[u])
    {
      if (dfn[v] == -1)
        dfs(v, from);
      check_min(low[u], low[v]);
    }
    if (low[u] >= dfn[u] && u != from)
    {
      puts("NO");
      std::cout << u + 1 << " " << from + 1 << std::endl;
      exit(0);
    }
  };

  dfs(0, 0);
  for (int i = 0; i < n; i++)
    if (dfn[i] == -1)
    {
      puts("NO");
      std::cout << 1 << " " << i + 1 << std::endl;
      exit(0);
    }

  puts("YES");

  return 0;
}
