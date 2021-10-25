#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int x = sc.next_int();
  std::vector<int> c(x + 1, 0x3f3f3f3f);
  c[0] = 0;

  for  (int i = 0; i < n; i++)
  {
    int a = sc.next_int();
    for (int j = a; j <= x; j++)
      check_min(c[j], c[j - a] + 1);
  }

  printf("%d\n", c[x] == 0x3f3f3f3f ? -1 :  c[x]);
  return 0;
}

