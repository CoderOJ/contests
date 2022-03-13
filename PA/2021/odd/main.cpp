#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
using int_t       = cm::intm<MOD>;

struct dp_t
{
  int_t invalid = 0;
  int_t valid   = 0;
};

std::ostream &operator<<(std::ostream &out, dp_t dp)
{
  return out << "(" << dp.invalid << ", " << dp.valid << ")";
}

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();

  std::vector<dp_t> dp(1);
  dp[0].invalid = 0;
  dp[0].valid   = 1;

  for (int i = 0; i < n; i++)
  {
    std::vector<dp_t> cur(dp.size() + 1);
    for (int i = 0; i < (int)dp.size(); i++)
    {
      cur[i].valid += dp[i].invalid * i;
      cur[i].invalid += dp[i].invalid * (m - i);
      cur[i].valid += dp[i].valid * i;
      cur[i + 1].invalid += dp[i].valid * (m - i);
    }
    dp = std::move(cur);
    see(i, dp);
  }

  int_t ans = 0;
  for (const auto &x : dp)
    ans += x.valid;
  std::cout << ans << std::endl;

  return 0;
}
