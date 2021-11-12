#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int q = sc.next_int();
  std::vector<std::vector<int>> a(n + 1, std::vector<int>(n + 1, 0));
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      a[i][j] =
          a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1] + (sc.next_char() == '*');
  for (int i = 0; i < q; i++)
  {
    int ux = sc.next_int() - 1;
    int uy = sc.next_int() - 1;
    int vx = sc.next_int();
    int vy = sc.next_int();
    std::cout << a[vx][vy] - a[ux][vy] - a[vx][uy] + a[ux][uy] << std::endl;
  }
  return 0;
}
