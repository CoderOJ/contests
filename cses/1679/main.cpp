#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <queue>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<int> dep_cnt(n);
  std::vector<std::vector<int>> e(n);
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    dep_cnt[v]++;
    e[u].push_back(v);
  }

  std::queue<int> que;
  for (int i = 0; i < n; i++)
    if (dep_cnt[i] == 0)
      que.push(i);

  std::vector<int> res;
  while (!que.empty())
  {
    int u = que.front();
    que.pop();
    res.push_back(u);
    for (int v : e[u])
    {
      dep_cnt[v]--;
      if (dep_cnt[v] == 0)
        que.push(v);
    }
  }

  if (static_cast<int>(res.size()) < n)
    puts("IMPOSSIBLE");
  else
  {
    for (int x : res)
      std::cout << x + 1 << " ";
  }

  return 0;
}
