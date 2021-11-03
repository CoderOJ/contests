#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  constexpr int B = 30;

  int n = sc.next_int();
  int q = sc.next_int();
  std::vector<std::vector<int>> next(n, std::vector<int>(B));
  for (int i = 0; i < n; i++)
    next[i][0] = sc.next_int() - 1;
  for (int b = 0; b + 1 < B; b++)
    for (int i = 0; i < n; i++)
      next[i][b + 1] = next[next[i][b]][b];

  for (int i = 0; i < q; i++)
  {
    int u = sc.next_int() - 1;
    int k = sc.next_int();
    for (int b = 0; b < B; b++)
      if (k & (1 << b))
        u = next[u][b];
    printf("%d\n", u + 1);
  }

  return 0;
}
