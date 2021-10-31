#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  constexpr int MOD = 1'000'000'007;
  using int_t = cm::intm<MOD>;

  int n = sc.next_int(), m = sc.next_int();

  std::vector<int_t> dp(1 << (n + 1));
  dp[0] = 1;

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      std::vector<int_t> cur(1 << (n + 1));
      for (int x = 0; x < (1 << (n + 1)); x++)
      {
        if (x & (1 << j))
        {
          if (x & (1 << (j + 1)))
            continue;
          else
            cur[x ^ (1 << j)] += dp[x];
        }
        else
        {
          if (x & (1 << (j + 1)))
            cur[x ^ (1 << (j + 1))] += dp[x];
          else
          {
            cur[x ^ (1 << j)] += dp[x];
            cur[x ^ (1 << (j + 1))] += dp[x];
          }
        }
      }
      dp = std::move(cur);
    }
    std::vector<int_t> cur(1 << (n + 1));
    for (int i = 0; i < (1 << n); i++)
      cur[i << 1] = dp[i];
    dp = std::move(cur);
  }

  std::cout << dp[0] << std::endl;

  return 0;
}

