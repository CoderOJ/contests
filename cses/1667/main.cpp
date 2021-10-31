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

  const int a = 1, b = n;
  std::vector<int> pre(n + 1, -1);
  pre[a] = a;
  std::queue<int> que;
  que.push(a);
  while (!que.empty())
  {
    int u = que.front();
    que.pop();
    for (int v : e[u])
      if (pre[v] == -1)
      {
        pre[v] = u;
        que.push(v);
      }
  }

  if (pre[b] == -1)
  {
    puts("IMPOSSIBLE");
    return 0;
  }

  std::vector<int> trace;
  for (int u = b; u != a; u = pre[u])
    trace.push_back(u);
  trace.push_back(a);
  std::reverse(trace.begin(), trace.end());
  std::cout << trace.size() << std::endl;
  for (int x : trace)
    std::cout << x << " ";

  return 0;
}
