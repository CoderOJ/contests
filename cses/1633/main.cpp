#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<int> dp(n + 1);
  dp[0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= 6; j++)
      if (i - j >= 0)
        dp[i] = (dp[i] + dp[i - j]) % 1'000'000'007;
  printf("%d\n", dp[n]);
  return 0;
}

