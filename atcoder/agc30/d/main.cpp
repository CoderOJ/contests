#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <tuple>
#include <type_traits>
#include <vector>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
using int_t = cm::intm<MOD>;
CONSTRAINT(N, 3000, 30)

int a[N], n, q;
int_t prob[N][N];

int main()
{
  const int_t i2 = int_t(2).inv();

  n = sc.next_int();
  q = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      prob[i][j] = a[i] > a[j] ? 1 : 0;

  for (int i = 0; i < q; i++)
  {
    int x = sc.next_int() - 1;
    int y = sc.next_int() - 1;
    if (x > y)
      std::swap(x, y);

    std::vector<std::tuple<int, int, int_t>> modifys;
    modifys.emplace_back(x, y, (prob[x][y] + prob[y][x]) * i2);
    modifys.emplace_back(y, x, (prob[x][y] + prob[y][x]) * i2);
    for (int i = 0; i < n; i++)
      if (i != y)
      {
        modifys.emplace_back(x, i, (prob[x][i] + prob[y][i]) * i2);
        modifys.emplace_back(i, x, (prob[i][x] + prob[i][y]) * i2);
      }
    for (int i = 0; i < n; i++)
      if (i != x)
      {
        modifys.emplace_back(i, y, (prob[i][y] + prob[i][x]) * i2);
        modifys.emplace_back(y, i, (prob[y][i] + prob[x][i]) * i2);
      }

    for (const auto &[x, y, v] : modifys)
      prob[x][y] = v;
  }

  int_t ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      ans += prob[i][j];
  std::cout << ans * int_t(2).pow(q) << std::endl;

  return 0;
}
