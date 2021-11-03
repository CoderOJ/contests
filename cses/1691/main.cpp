#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<std::vector<std::pair<int, int>>> e(n);
  std::vector<int> deg(n);
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u].emplace_back(v, i);
    e[v].emplace_back(u, i);
    deg[u]++;
    deg[v]++;
  }

  if (std::any_of(deg.begin(), deg.end(), [](int x) { return x % 2 == 1; }))
  {
    puts("IMPOSSIBLE");
    return 0;
  }

  std::vector<std::vector<std::pair<int, int>>::iterator> e_cur(n);
  for (int i = 0; i < n; i++)
    e_cur[i] = e[i].begin();
  std::vector<bool> e_vis(m, false);

  std::vector<int> ans;
  std::function<void(int)> dfs = [&](int u) {
    for (auto &it = e_cur[u]; it != e[u].end();)
    {
      if (e_vis[it->second])
      {
        it++;
        continue;
      }
      else
      {
        e_vis[it->second] = true;
        dfs(it++->first);
      }
    }
    ans.push_back(u);
  };

  dfs(0);
  if (static_cast<int>(ans.size()) < m + 1)
  {
    puts("IMPOSSIBLE");
    return 0;
  }
  for (int x : ans)
    std::cout << x + 1 << " ";

  return 0;
}
