#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <ext/rope>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  __gnu_cxx::rope<int> a;
  for (int i = 0; i < n; i++)
    a.push_back(sc.next_int());
  for (int i = 0; i < n; i++)
  {
    int p = sc.next_int() - 1;
    printf("%d ", a[p]);
    a.erase(p, 1);
  }
  return 0;
}

