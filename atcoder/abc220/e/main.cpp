#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <numeric>

cm::scanner<cm::optimal_reader> sc(stdin);
using int_t = cm::intm<998244353>;
constexpr int N = 2000005;
int n, d;

int_t p2[N];
int_t cnt[N];

int main()
{
  int n = sc.next_int();
  int d = sc.next_int();

  p2[0] = 1;
  for (int i = 1; i < N; i++)
    p2[i] = p2[i - 1] * 2;

  for (int i = 0; i <= d; i++)
  {
    cnt[i] = p2[d - i];
    if (i != 0 && d != i) cnt[i] -= p2[d - i - 1];
  }

  std::partial_sum(cnt, cnt + n + 1, cnt);

  int_t ans = 0;
  for (int i = 0; i < n; i++)
  {
    int l = std::max(0, (d - (n - i - 1) + 1) / 2);
    int r = std::min(i, d);
    if (r < l) continue;
    int_t cur = cnt[r] - (l ? cnt[l - 1] : 0);
    ans += cur * p2[i];
    see(i, l, r, cur);
  }

  std::cout << ans << std::endl;

  return 0;
}

