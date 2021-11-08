#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <vector>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  constexpr int MOD = 1'000'000'007;
  using int_t = cm::intm<MOD>;

  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<std::vector<int_t>> e(n, std::vector<int_t>(n, 0));
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u][v] += 1;
  }

  int mask_all = (1 << n) - 1;
  std::vector<std::vector<int_t>> cnt(1 << n, std::vector<int_t>(n));
  cnt[1][0] = 1;

  for (int i = 2; i <= mask_all; i++)
    for (int v = 0; v < n; v++)
      if (i & (1 << v))
        for (int u = 0; u < n; u++)
          cnt[i][v] += e[u][v] * cnt[i ^ (1 << v)][u];

  std::cout << cnt[mask_all][n - 1] << std::endl;

  return 0;
}
