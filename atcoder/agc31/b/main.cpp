#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <iterator>
#include <vector>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  constexpr int MOD = 1'000'000'007;
  using int_t = cm::intm<MOD>;

  int n = sc.next_int();
  std::vector<int> a(n);
  for (int &x : a)
    x = sc.next_int() - 1;

  int m = *std::max_element(a.begin(), a.end()) + 1;
  std::vector<int_t> pre_sum(m);
  std::vector<int_t> dp(n + 1);
  dp[0] = 1;
  for (int i = 0; i < n; i++)
  {
    if (i == 0 || a[i] != a[i - 1])
      pre_sum[a[i]] += dp[i];
    dp[i + 1] = pre_sum[a[i]];
  }

  std::cout << dp[n] << std::endl;

  return 0;
}
