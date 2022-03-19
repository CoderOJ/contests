#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include <bit>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1000000007;
constexpr int N   = 16;
using int_t       = cm::intm<MOD>;
using mask_t      = uint32_t;

mask_t e[N];
int    n, m;

int_t pow2[N * N];
int_t f[1 << N], g[1 << N];

int_t count_e(mask_t a, mask_t b)
{
  int res = 0;
  for (int i = 0; i < n; i++)
    if (a & (1 << i))
      res += std::popcount(e[i] & b);
  return pow2[res];
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u] |= (1 << v);
  }

  pow2[0] = 1;
  for (int i = 1; i < N * N; i++)
    pow2[i] = pow2[i - 1] * 2;

  f[0] = 1;
  g[0] = 1;
  for (int b = 1; b < (1 << n); b++)
  {
    g[b] = 0;
    for (int s = b; s > 0; s = (s - 1) & b)
      g[b] -= g[b ^ s] * count_e(b, s);
    f[b] = g[b];
    for (int s = (b - 1) & b; s > 0; s = (s - 1) & b)
      if (s > (b ^ s))
        f[b] -= f[s] * g[b ^ s];
  }

  std::cout << 0 - f[(1 << n) - 1] << std::endl;

  return 0;
}
