#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#include <set>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int k = sc.next_int();
  std::vector<std::pair<int,int>> a;
  for (int i = 0; i < n; i++)
  {
    int l = sc.next_int();
    int r = sc.next_int();
    a.emplace_back(l, r);
  }
  std::sort(a.begin(), a.end(), [](auto x, auto y) { return x.second < y.second; });
  std::multiset<int> ava;
  for (int i = 0; i < k; i++) ava.insert(0);

  int ans = 0;
  for (const auto& [l,r] : a)
  {
    auto it = ava.upper_bound(l);
    if (it != ava.begin()) { --it; ava.erase(it); ava.insert(r); ans++; }
  }
  std::cout << ans << std::endl;

  return 0;
}

