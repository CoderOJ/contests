#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <functional>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<std::vector<int>> e(n);
  for (int i = 1; i < n; i++)
    e[sc.next_int() - 1].push_back(i);

  std::vector<int> size(n, 1);
  std::function<void(int)> dfs = [&](int u) {
    for (int v : e[u])
    {
      dfs(v);
      size[u] += size[v];
    }
  };

  dfs(0);
  for (int i = 0; i < n; i++)
    std::cout << size[i] - 1 << " ";

  return 0;
}
