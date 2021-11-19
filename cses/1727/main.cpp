#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cmath>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  double ans = m * pow(m, n);
  for (int i = 1; i < m; i++)
    ans -= pow(i, n);
  printf("%.6lf\n", ans / pow(m, n));
  return 0;
}
