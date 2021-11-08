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

  std::function<std::pair<bool, int>(int, int)> dfs = [&](int u, int f) -> std::pair<bool,int> {
    bool matched = false;
    int cur_ans = 0;
    for (int v : e[u]) if (v != f)
    {
      const auto [vm, va] = dfs(v, u);
      if (!vm && !matched)
      {
        matched = true;
        cur_ans += va + 1;
      }
      else
      {
        cur_ans += va;
      }
    }
    return std::make_pair(matched, cur_ans);
  };

  std::cout << dfs(0, 0).second << std::endl;
  return 0;
}
