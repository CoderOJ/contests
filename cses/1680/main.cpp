#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <iterator>
#include <limits>
#include <queue>
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
    e[u].push_back(v);
    degree[v]++;
  }

  std::vector<int> pre(n, -1);
  std::vector<int> dis(n, std::numeric_limits<int>::min() / 2);
  dis[0] = 0;
  std::queue<int> que;
  for (int i = 0; i < n; i++)
    if (degree[i] == 0)
      que.push(i);
  while (!que.empty())
  {
    int u = que.front();
    que.pop();
    for (int v : e[u])
    {
      if (check_max(dis[v], dis[u] + 1))
        pre[v] = u;
      if (--degree[v] == 0)
        que.push(v);
    }
  }

  std::vector<int> ans;
  for (int u = n - 1; u != -1; u = pre[u])
    ans.push_back(u);
  std::reverse(ans.begin(), ans.end());
  if (ans[0] != 0)
  {
    puts("IMPOSSIBLE");
  }
  else
  {
    std::cout << ans.size() << std::endl;
    for (int x : ans)
      std::cout << x + 1 << " ";
  }

  return 0;
}
