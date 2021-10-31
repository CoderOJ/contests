#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

#include <limits>

int main()
{
#define int long long

  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<std::tuple<int, int, int>> es;
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1, v = sc.next_int() - 1, w = sc.next_int();
    es.emplace_back(u, v, w);
  }

  std::vector<int> dis(n, std::numeric_limits<int>::min() / 2);
  dis[0] = 0;
  for (int i = 0; i < n; i++)
    for (const auto &[u, v, w] : es)
      check_max(dis[v], dis[u] + w);
  auto ori_dis = dis;

  int ans = dis[n - 1];
  for (int i = 0; i < n; i++)
    for (const auto &[u, v, w] : es)
      check_max(dis[v], dis[u] + w);

  std::vector<bool> inf_u(n, false);
  for (int i = 0; i < n; i++)
    if (dis[i] >= std::numeric_limits<int>::min() / 4 && dis[i] != ori_dis[i])
      inf_u[i] = true;
  for (const auto &[u, v, w] : es)
    inf_u[v] = inf_u[v] | inf_u[u];

  if (inf_u[n - 1])
    puts("-1");
  else
    printf("%lld\n", ans);

  return 0;
}
