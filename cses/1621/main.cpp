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
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  std::sort(a.begin(), a.end());
  std::cout << std::unique(a.begin(), a.end()) - a.begin() << std::endl;
  return 0;
}

