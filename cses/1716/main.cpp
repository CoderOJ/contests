#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
using int_t = cm::intm<MOD>;
CONSTRAINT(N, 2000005, 1005)
int_t fac[N], inv[N], ifac[N];

int main()
{
  fac[0] = fac[1] = 1;
  inv[0] = inv[1] = 1;
  ifac[0] = ifac[1] = 1;
  for (int i = 2; i < N; i++)
  {
    fac[i] = fac[i - 1] * i;
    inv[i] = inv[MOD % i] * (MOD - MOD / i);
    ifac[i] = ifac[i - 1] * inv[i];
  }

  auto binom = [](int n, int m)
  {
    return fac[n] * ifac[m] * ifac[n - m];
  };

  int n = sc.next_int();
  int m = sc.next_int();
  std::cout << binom(m + n - 1, n - 1);

  return 0;
}
