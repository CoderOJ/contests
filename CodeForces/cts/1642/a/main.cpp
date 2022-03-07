#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cmath>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int x1 = sc.next_int();
    int y1 = sc.next_int();
    int x2 = sc.next_int();
    int y2 = sc.next_int();
    int x3 = sc.next_int();
    int y3 = sc.next_int();
    double ans = 0;
    if (y1 == y2 && y1 > y3)
      ans += std::hypot(x1 - x2, y1 - y2);
    if (y2 == y3 && y2 > y1)
      ans += std::hypot(x2 - x3, y2 - y3);
    if (y3 == y1 && y3 > y2)
      ans += std::hypot(x3 - x1, y3 - y1);
    printf("%.12lf\n", ans);
  }
  return 0;
}
