#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm_alpha"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 998'244'353;
using int_t = cm::intm<MOD>;

int main()
{
  int n = sc.next_int();
  int k = sc.next_int();
  if (k > n) k = n;

  std::vector<int_t> fac(n + 1), ifac(n + 1);
  fac[0] = ifac[0] = ifac[1] = int_t::raw(1);
  for (int i = 2; i <= n; i++)
    ifac[i] = int_t::raw(MOD - MOD / i) * ifac[MOD % i];
  for (int i = 1; i <= n; i++)
  {
    fac[i] = fac[i - 1] * int_t::raw(i);
    ifac[i] *= ifac[i - 1];
  }

  std::vector<int_t> f(n + 1), p(n + 1);
  for (int i = 1; i <= k; i++)
  {
    f[i] = fac[i];
    p[i] = p[i - 1] + cm::intm_r<MOD, 1>(1);
  }
  for (int i = k + 1; i <= n; i++)
  {
    f[i] = fac[i - 1] * (p[i - 1] - p[i - k - 1]);
    p[i] = p[i - 1] + f[i] * ifac[i];
  }

  std::cout << f[n] << std::endl;

  return 0;
}

