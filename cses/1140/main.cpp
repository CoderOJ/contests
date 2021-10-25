#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
#define int long long

  int n = sc.next_int();
  std::vector<std::tuple<int,int,int>> a(n);
  std::vector<int> vals; vals.reserve(n * 2);
  for (auto& [r,l,w] : a)
  {
    l = sc.next_int();
    r = sc.next_int();
    w = sc.next_int();
    vals.push_back(l);
    vals.push_back(r);
  }

  std::sort(vals.begin(), vals.end());
  vals.erase(std::unique(vals.begin(), vals.end()), vals.end());

  for (auto& [r,l,w] : a)
  {
    l = static_cast<int>(std::lower_bound(vals.begin(), vals.end(), l) - vals.begin());
    r = static_cast<int>(std::lower_bound(vals.begin(), vals.end(), r) - vals.begin());
  }

  std::sort(a.begin(), a.end());

  std::vector<int> dp(vals.size(), 0);
  std::vector<int> prefix_max(vals.size(), 0);
  int pm_l = 0;
  for (const auto& [r,l,w] : a)
  {
    while (pm_l < r)
    {
      prefix_max[pm_l] = std::max(pm_l ? prefix_max[pm_l - 1] : 0, dp[pm_l]);
      pm_l++;
    }
    check_max(dp[r], (l ? prefix_max[l - 1] : 0) + w);
  }

  printf("%lld\n", *std::max_element(dp.begin(), dp.end()));

  return 0;
}

