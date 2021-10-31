#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <limits>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
#define int long long

  int n = sc.next_int(), m = sc.next_int(), q = sc.next_int();
  std::vector<std::vector<int>> dis(
      n, std::vector<int>(n, std::numeric_limits<int>::max() / 4));
  for (int i = 0; i < n; i++)
    dis[i][i] = 0;
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    int w = sc.next_int();
    check_min(dis[u][v], w);
    check_min(dis[v][u], w);
  }

  for (int r = 0; r < n; r++)
    for (int u = 0; u < n; u++)
      for (int v = 0; v < n; v++)
        check_min(dis[u][v], dis[u][r] + dis[r][v]);

  for (int i = 0; i < q; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    if (dis[u][v] >= std::numeric_limits<int>::max() / 4)
      puts("-1");
    else
      printf("%lld\n", dis[u][v]);
  }
  return 0;
}
