#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<int> dp(n + 1, 0x3f3f3f3f);
  dp[0] = 0;
  
  for (int i = 1; i <= n; i++)
    for (int c = i; c; c /= 10)
      check_min(dp[i], dp[i - c % 10] + 1);

  printf("%d\n", dp[n]);
  return 0;
}

