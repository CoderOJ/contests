#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/math_util"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <numeric>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
constexpr int N   = 1505;

using int_t = cm::intm<MOD>;
using mu    = cm::math_util<int_t>;

int n, m, k;

int_t  pa, pb, p;
int_t  p0[N], p1[N];
int_t  p_pr0[2][N], p_pr1[2][N], p_pr2[2][N];
int_t *pr0[N], *pr1[N], *pr2[N];

int main()
{
  n  = sc.next_int();
  m  = sc.next_int();
  pa = sc.next_int();
  pb = sc.next_int();
  k  = sc.next_int();
  p  = pa / pb;

  for (int i = 0; i <= std::min(m, k); i++)
    p0[i] = p.pow(i) * (1 - p).pow(k - i) * mu::binom.get(k, i);
  std::partial_sum(p0, p0 + m + 1, p1);

  for (int i = 0; i <= n; i++)
  {
    pr0[i] = p_pr0[i % 2];
    pr1[i] = p_pr1[i % 2];
    pr2[i] = p_pr2[i % 2];
  }

  auto make_pr = [](int i) {
    std::partial_sum(pr0[i], pr0[i] + m + 1, pr1[i]);
    for (int j = 0; j <= m; j++)
      pr2[i][j] = pr1[i][j] * p0[j];
    std::partial_sum(pr2[i], pr2[i] + m + 1, pr2[i]);
  };

  int_t psum = 1;
  pr0[0][m]  = 1;
  make_pr(0);

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
    {
      int_t s_prob = p0[m - j] * p1[j - 1];
      // clang-format off
      pr0[i][j] = psum * s_prob
                - pr1[i - 1][m - j] * s_prob
                - pr2[i - 1][j - 1] * p0[m - j];
      // clan-format on
    }
    make_pr(i);
    psum = pr1[i][m];
  }

  std::cout << pr1[n][m] << std::endl;

  return 0;
}