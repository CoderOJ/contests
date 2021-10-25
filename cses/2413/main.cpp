#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  constexpr int N = 1000005;
  constexpr int MOD = 1'000'000'007;
  struct dp_t
  {
    int split, joint;
  };

  std::vector<dp_t> dp(N);
  dp[1] = {1, 1};
  for (int i = 2; i < N; i++)
  {
    dp[i].split = (4ll * dp[i-1].split + dp[i-1].joint) % MOD;
    dp[i].joint = (dp[i-1].split + 2ll * dp[i-1].joint) % MOD;
  }

  int n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    int a = sc.next_int();
    printf("%d\n", (dp[a].split + dp[a].joint) % MOD);
  }

  return 0;
}

