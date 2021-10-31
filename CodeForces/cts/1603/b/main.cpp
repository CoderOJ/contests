#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int T = sc.next_int();
  for (int i = 0; i < T; i++)
  {
    int x = sc.next_int(), y = sc.next_int();
    if (x > y)
      printf("%d\n", x + y);
    else
      printf("%d\n", y - y % x / 2);
  }
  return 0;
}
