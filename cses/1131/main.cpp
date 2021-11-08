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
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  int ans = 0;
  std::function<int(int, int)> dfs = [&](int u, int f) -> int {
    int cur = 0;
    for (int v : e[u])
      if (v != f)
      {
        int v_dis = dfs(v, u) + 1;
        check_max(ans, cur + v_dis);
        check_max(cur, v_dis);
      }
    return cur;
  };


  dfs(0, 0);
  std::cout << ans << std::endl;

  return 0;
}
