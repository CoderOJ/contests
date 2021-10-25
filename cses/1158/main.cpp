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
  int x = sc.next_int();
  std::vector<int> dp(x + 1, 0);

  std::vector<int> v(n), w(n);
  for (int i = 0; i < n; i++)
    v[i] = sc.next_int();
  for (int i = 0; i < n; i++)
    w[i] = sc.next_int();

  for (int i = 0; i < n; i++)
    for (int j = x; j >= v[i]; j--)
      check_max(dp[j], dp[j - v[i]] + w[i]);

  printf("%d\n", *std::max_element(dp.begin(), dp.end()));
  return 0;
}

