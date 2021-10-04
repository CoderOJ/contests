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
    int l = sc.next_int();
    int r = sc.next_int();
    a.emplace_back(l, r);
  }

  std::sort(a.begin(), a.end(), [](auto x, auto y) { return x.second < y.second; });
  int cur_r = 0, ans = 0;
  for (const auto& [l,r] : a)
    if (l >= cur_r)
    {
      cur_r = r;
      ans++;
    }

  std::cout << ans << std::endl;

  return 0;
}

