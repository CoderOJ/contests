#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"
#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);
constexpr int MOD = 1000000007;
constexpr int N = 3005;
using int_t = cm::intm<MOD>;

int n, s[N], t[N], s_cnt[N], t_cnt[N];
int_t fac[N], s2t[N][N], t2s[N][N];


int main()
{
  fac[0] = 1;
  for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i;

  n = sc.next_int();
  for (int i = 0; i < n; i++) s[i] = sc.next_int(); std::sort(s, s + n);
  for (int i = 0; i < n; i++) t[i] = sc.next_int(); std::sort(t, t + n);
  for (int i = 0; i < n; i++) s_cnt[i] = (int)std::count_if(t, t + n, [i](int x) { return x >= s[i]; });
  for (int i = 0; i < n; i++) t_cnt[i] = (int)std::count_if(s, s + n, [i](int x) { return x <= t[i]; });
  
  t2s[0][0] = 1;
  for (int i = 0; i < n; i++)
  {
    t2s[i + 1][0] = 1;
    for (int j = 0; j <= i; j++)
      t2s[i + 1][j + 1] = t2s[i][j + 1] + t2s[i][j] * std::max(t_cnt[i] - j, 0);
  }

  s2t[n][0] = 1;
  for (int i = n; i > 0; i--)
  {
    s2t[i - 1][0] = 1;
    for (int j = 0; j <= n - i; j++)
      s2t[i - 1][j + 1] = s2t[i][j + 1] + s2t[i][j] * std::max(s_cnt[i - 1] - j, 0);
  }

  int_t ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j <= std::min(i, s_cnt[i]); j++)
      ans += fac[j] * t2s[n - s_cnt[i]][i - j] * s2t[i + 1][s_cnt[i] - j];

  std::cout << ans + t2s[n][n] << std::endl;
  return 0;
}

