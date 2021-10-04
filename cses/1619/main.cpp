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
  std::vector<std::pair<int,int>> a;
  for (int i = 0; i < n; i++)
  {
    a.emplace_back(sc.next_int(), 1);
    a.emplace_back(sc.next_int(), -1);
  }

  std::sort(a.begin(), a.end());
  int cur = 0, ans = 0;
  for (const auto & [x, det] : a)
    check_max(ans, cur += det);

  std::cout << ans << std::endl;

  return 0;
}

