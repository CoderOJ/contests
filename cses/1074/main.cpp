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

  int goal = a[a.size() / 2];
  long long ans = 0;
  for (int x: a) ans += std::abs(x - goal);
  std::cout << ans << std::endl;
  return 0;
}

