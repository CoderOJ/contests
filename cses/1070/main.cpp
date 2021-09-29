#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  if (n == 2 || n == 3)
  {
    puts("NO SOLUTION");
    return 0;
  }

  for (int i = 2; i <= n; i += 2)
    printf("%d ", i);
  for (int i = 1; i <= n; i += 2)
    printf("%d ", i);
  return 0;
}

