#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  int q = sc.next_int();

  std::vector<std::vector<int>> a(n, std::vector<int>(m, 0));

  int ans = 0;
  auto flip = [&](int x, int y)
  {
    if (x >= 0 && y >= 0)
    {
    ans -= a[x][y];
    a[x][y] = !a[x][y];
    ans += a[x][y];
    }
  };

  for (int i = 0; i < q; i++)
  {
    int x1 = sc.next_int() - 2;
    int y1 = sc.next_int() - 2;
    int x2 = sc.next_int() - 1;
    int y2 = sc.next_int() - 1;
    flip(x2, y2);
    flip(x2, y1);
    flip(x1, y2);
    flip(x1, y1);
    printf("%d\n", ans);
  }

  return 0;
}
