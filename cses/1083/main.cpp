#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<int> a(n - 1);
  for (int i = 0; i < n - 1; i++)
    a[i] = sc.next_int();
  std::sort(a.begin(), a.end());
  for (int i = 0; i < n - 1; i++)
    if (a[i] != i + 1)
    {
      printf("%d\n", i + 1);
      return 0;
    }
  printf("%d\n", n);
  return 0;
}

