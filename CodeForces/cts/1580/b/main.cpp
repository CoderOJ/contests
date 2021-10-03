#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/code/creats/Intdm.hpp"
// #include "/home/jack/cm/string"

#include <cstring>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 105;
using int_t = Temps::Intdm<0>;
int_t fac[N], c[N][N], f[N][N][N];
int n, m, k;

int_t dp(int size, int cnt, int dep)
{
  int_t &ans = f[dep][size][cnt];
  if (ans != -1) return ans;
  ans = 0;

  if (size == 0) return ans = 1;
  if ((m - dep < 7 && 
      (1 << (m - dep)) < cnt) || (cnt && size < m - dep))
    return ans;
  if (dep == m)
    return ans = (cnt == 1 ? fac[size] : 0);

  for (int i = 0; i < size; i++)
  {
    int_t fi = 0;
    for (int j = std::max(0, cnt + i + 1 - size); j <= std::min(cnt, i); j++)
      fi += dp(i, j, dep + 1) * dp(size - i - 1, cnt - j,  dep + 1);
    ans += fi * c[size - 1][i];
  }

  return ans;
}

int main()
{
  n = sc.next_int();
  m = sc.next_int() - 1;
  k = sc.next_int();
  int_t::set_mod(sc.next_int());

  c[0][0] = fac[0] = 1;
  for (int i = 1; i <= n; i++)
  {
    c[i][0] = 1;
    fac[i] = fac[i - 1] * i;
    for (int j = 1; j <= i; j++)
      c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
  }

  memset(f, -1, sizeof(f));
  dp(n, k, 0);
  std::cout << f[0][n][k] << std::endl;

  return 0;
}
