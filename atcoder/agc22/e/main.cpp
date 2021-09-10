#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1000000007;
constexpr int N = 300005;
char s[N], *se;
using int_t = cm::intm<MOD>;

struct state_t
{
  int_t dp[3][3];
  void trans_by_zero(state_t &rhs)
  {
    for (int a = 0; a < 3; a++)
    {
      rhs.dp[a][1] += dp[a][2];
      rhs.dp[a][1] += dp[a][0];
      rhs.dp[a][2] += dp[a][1];
    }
  }
  void trans_by_one(state_t &rhs)
  {
    for (int a = 0; a < 3; a++)
    {
      rhs.dp[a][0] += dp[a][1];
      rhs.dp[a][1] += dp[a][2];
    }
    rhs.dp[1][0] += dp[0][0];
    rhs.dp[2][0] += dp[1][0];
    rhs.dp[2][0] += dp[2][0];
  }
};

int main()
{
  se = sc.next_token(s);
  state_t pos; pos.dp[0][0] = 1;
  for (char *i = s; i < se; i++)
  {
    state_t cur;
    if (*i != '1') pos.trans_by_zero(cur);
    if (*i != '0') pos.trans_by_one(cur);
    pos = cur;
  }

  int_t ans = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (i >= j)
        ans += pos.dp[i][j];
  std::cout << ans << std::endl;
  return 0;
}

