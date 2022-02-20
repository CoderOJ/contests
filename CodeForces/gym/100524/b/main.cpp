#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/math_util"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

#ifdef CM_DEBUG
cm::scanner<cm::optimal_reader> sc(stdin);
FILE                           *output = stdout;
#else
cm::scanner<cm::optimal_reader> sc(fopen("bipartite.in", "r"));
FILE                           *output = fopen("bipartite.out", "w");
#endif

constexpr int MOD = 175781251;
using int_t       = cm::intm<MOD>;
using mu          = cm::math_util<int_t>;

constexpr int n = 105;

int_t f[n], g[n], h[n];

int main()
{
  for (int i = 1; i < n; i++)
    for (int j = 1; j <= i; j++)
      f[i] += mu::binom.get(i - 1, j - 1) * int_t(3).pow(j * (i - j));

  for (int i = 1; i < n; i++)
  {
    g[i] = f[i];
    for (int j = 1; j < i; j++)
      g[i] -= g[j] * f[i - j] * mu::binom.get(i - 1, j - 1) * 2;
  }

  h[0] = 1;
  for (int i = 1; i < n; i++)
    for (int j = 1; j <= i; j++)
      h[i] += h[i - j] * g[j] * mu::binom.get(i - 1, j - 1);

  while (true)
  {
    int n = sc.next_int();
    if (n == 0)
      break;
    fprintf(output, "%d\n", static_cast<int>(h[n]));
  }

  return 0;
}
