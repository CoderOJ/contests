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
    int n = sc.next_int();

    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int();

    int l = -1, r = -1;
    for (int i = 0; i < n; i++)
      if (a[i] == 0)
      {
        if (l == -1)
          l = i;
        r = i;
      }

    if (l == -1)
      puts("0");
    else 
      std::cout << r - l + 2 << std::endl;
  }
  return 0;
}
