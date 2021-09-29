#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int a = sc.next_int();
    int b = sc.next_int();
    if ((a + b) % 3 == 0 && a <= b * 2 && b <= a * 2)
      puts("YES");
    else
      puts("NO");
  }
  return 0;
}

