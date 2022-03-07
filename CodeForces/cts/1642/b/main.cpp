#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int              n = sc.next_int();
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int();
    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());
    int k = static_cast<int>(a.size());
    for (int i = 1; i <= n; i++)
      printf("%d ", std::max(k, i));
    puts("");
  }
  return 0;
}
