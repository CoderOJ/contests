#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <functional>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<std::vector<int>> e(n);
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  std::function<int(int, int)> dfs = [&](int u, int f) {
    int size = 1;
    int cur_val = 0;
    for (int v : e[u])
      if (v != f)
      {
        int v_size = dfs(v, u);
        check_max(cur_val, v_size);
        size += v_size;
      }
    check_max(cur_val, n - size);
    if (cur_val <= (n / 2))
      throw u;
    return size;
  };

  try
  {
    dfs(0, 0);
  }
  catch (int ans)
  {
    std::cout << ans + 1 << std::endl;
  }

  return 0;
}
