#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstring>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 13;
constexpr int M = 505;

int n, m;
int a[N];

int64_t dp[1 << N][N][M];

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  int max_id = 0;
  for (int i = 0; i < n; i++)
    if (a[i] > a[max_id])
      max_id = i;

  for (int32_t mask = (1u << n) - 1; mask >= 0; mask--)
  {
    int remain_cnt = n - __builtin_popcount(mask);
    for (int remain = 0; remain <= m; remain++)
      for (int pre = 0; pre < n; pre++)
      {
        if (remain_cnt == 0)
          dp[mask][pre][remain] = 1;

        for (int i = 0; i < n; i++)
          if ((mask & (1u << i)) == 0)
          {
            int det      = std::max(a[pre] - a[i] + (i > pre), 0);
            int v_remain = remain - remain_cnt * det;
            if (v_remain >= 0)
              dp[mask][pre][remain] += dp[mask | (1u << i)][i][v_remain];
          }
      }
  }

  std::cout << dp[0][max_id][m] << std::endl;

  return 0;
}
