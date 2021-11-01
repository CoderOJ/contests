#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <iostream>
#include <limits>
#include <ostream>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<std::tuple<int, int, int>> es;
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    int w = sc.next_int();
    es.emplace_back(u, v, w);
  }

  std::vector<long long> dis(n, std::numeric_limits<long long>::max() / 2);
  std::vector<int> pre(n, -1);
  dis[0] = 0;

  int last_update;
  for (int i = 0; i < n * 2; i++)
  {
    last_update = -1;
    for (const auto &[u, v, w] : es)
      if (cm::check_min(dis[v], dis[u] + w))
      {
        pre[v] = u;
        last_update = v;
      }
  }

  if (last_update == -1)
    puts("NO");
  else
  {
    puts("YES");
    std::vector<int> ans;
    std::vector<bool> vis(n, false);
    for (int u = last_update;; u = pre[u])
    {
      ans.push_back(u);
      if (vis[u])
        break;
      vis[u] = true;
    }
    std::reverse(ans.begin(), ans.end());
    while (ans.back() != ans[0])
      ans.pop_back();
    for (const int x : ans)
      std::cout << x + 1 << " ";
  }

  return 0;
}
