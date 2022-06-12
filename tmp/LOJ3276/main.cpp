#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/math_util"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

const int MOD = 1'000'000'007;
using int_t   = cm::intm<MOD>;
using mu      = cm::math_util<int_t>;

CONSTRAINT(N, 605, 40)
int_t f[N][N], g[N * 2][N];
bool  a[N * 2];
int   n;

int main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    int p = sc.next_int() - 1;
    a[p]  = true;
  }
  mu::fac.require(n);
  mu::ifac.require(n);

  f[0][0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= i; j++)
      f[i][j] = f[i - 1][j] + (j >= 1 ? 2 * f[i - 1][j - 1] : 0) +
                (j >= 2 ? f[i - 1][j - 2] : 0);

  int c0 = 0, c1 = 0;
  g[n + n][0] = 1;
  for (int i = n * 2 - 1; i >= 0; i--)
  {
    if (a[i])
    {
      for (int j = 0; j <= c1; j++)
        if (g[i + 1][j])
        {
          g[i][j] += g[i + 1][j];
          for (int k = 0; j + 1 + k <= c1 + 1; k++)
            g[i][j + 1 + k] += g[i + 1][j] * (k + 2) * f[k][k] *
                               mu::fac(c1 - j) * mu::ifac(c1 - j - k);
        }
      c1++;
    }
    else
    {
      for (int j = c0 + 1; j <= c1; j++)
        g[i][j] += g[i + 1][j] * (j - c0);
      c0++;
    }

    // for (int j = 0; j <= n; j++)
    //   ee(i, j, g[i][j]);
  }

  int_t ans = g[0][n] / int_t(2).pow(n);
  std::cout << ans << std::endl;

  return 0;
}
