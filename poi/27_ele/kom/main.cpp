#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <functional>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();

  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  std::sort(a.begin(), a.end());

  if (n == 1)
  {
    puts("1");
    puts("0");
    return 0;
  }

  std::vector<int> first(a.back() + 1);
  for (int i = 1; i < n; i++)
    if (a[i - 1] != a[i])
      first[a[i]] = i;

  std::vector<int> dp(n + 1);
  dp[0] = 0;
  for (int i = 1; i <= n; i++)
  {
    dp[i]       = 0x3f3f3f3f;
    int cur_len = i - first[a[i - 1]];
    int pre_len = (i == cur_len || a[i - cur_len - 1] + 1 != a[i - 1])
                      ? 0
                      : (i - cur_len) - first[a[i - cur_len - 1]];
    for (int j = 1;; j *= 2)
    {
      int cur = std::min(cur_len, j);
      if ((j - cur) % 2 == 1)
        break;
      int pre = (j - cur) / 2;
      if (pre > pre_len)
        break;
      check_min(dp[i], dp[i - cur - pre] + 1);
      see(i, j, cur, pre);
    }
  }

  std::cout << dp[n] * 2 - 1 << std::endl;
  for (int x : a)
    std::cout << x << " ";
  std::cout << std::endl;

  return 0;
}
