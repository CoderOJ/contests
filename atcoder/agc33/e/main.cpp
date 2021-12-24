#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
constexpr int N = 500005;
using int_t = cm::intm<MOD>;
int n, m, p[N], next[N];

int_t dp[N];
void solve_all1()
{
  if (n == 1)
    puts("1");
  else if (n == 2)
    puts("3");
  else
  {
    dp[0] = 1;
    dp[1] = 2;
    for (int i = 2; i <= n; i++)
      dp[i] = dp[i - 1] + dp[i - 2];
    std::cout << dp[n - 1] + dp[n - 3] << std::endl;
  }
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 1; i <= m; i++)
    p[i] = sc.next_char() == 'R';
  if (p[1] == 0)
    for (int i = 1; i <= m; i++)
      p[i] ^= 1;

  next[m + 1] = m + 1;
  for (int i = m; i >= 1; i--)
    next[i] = p[i] ? next[i + 1] : i;

  if (next[1] == m + 1)
    solve_all1();
  else if (n % 2 == 1)
    puts("0");
  else
  {
    int min_len = next[1];
    for (int i = 1; i <= m; i++)
      if (next[i] != m + 1 && p[i - 1] == 0)
      {
        int cur_len = next[i] - i;
        if (cur_len % 2 == 1)
          check_min(min_len, cur_len);
      }

    if (min_len % 2 == 0)
      min_len--;

    n = n / 2;
    min_len = (min_len + 1) / 2;
    int_t s = 0;
    for (int i = 1; i <= n; i++)
    {
      if (i > min_len)
        s = s - dp[i - min_len - 1];
      dp[i] = s + (i <= min_len ? i * 2 : 0);
      s += dp[i];
    }
    std::cout << dp[n] << std::endl;
  }

  return 0;
}
