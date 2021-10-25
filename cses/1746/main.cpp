#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <numeric>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<int> dp(m + 2);
  int a0 = sc.next_int();
  if (a0 != 0) dp[a0] = 1;
  else dp = std::vector<int>(m + 2, 1), dp[0] = dp[m + 1] = 0;
  for (int i = 1; i < n; i++)
  {
    int a = sc.next_int();
    std::vector<int> cur(m + 2);
    for (int i = 1; i <= m; i++)
      if (a == 0 || a == i)
        cur[i] = (0ll + dp[i - 1] + dp[i] + dp[i + 1]) % 1'000'000'007;
    dp = std::move(cur);
  }

  std::cout << std::accumulate(dp.begin(), dp.end(), 0ll) % 1'000'000'007 << std::endl;
  return 0;
}

