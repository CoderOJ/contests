#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) a[i] = (i + 1) % n;
  int p = 0;
  for (int i = 0; i < n; i++)
  {
    std::cout << a[p] + 1 << " ";
    a[p] = a[a[p]];
    p = a[p];
  }
  return 0;
}

