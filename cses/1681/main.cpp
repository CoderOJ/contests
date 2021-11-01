#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <iterator>
#include <limits>
#include <queue>
#include <vector>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  constexpr int MOD = 1'000'000'007;
  using int_t = cm::intm<MOD>;

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

  std::vector<int_t> cnt(n);
  cnt[0] = 1;
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
      cnt[v] += cnt[u];
      if (--degree[v] == 0)
        que.push(v);
    }
  }

  std::cout << cnt[n - 1] << std::endl;

  return 0;
}
