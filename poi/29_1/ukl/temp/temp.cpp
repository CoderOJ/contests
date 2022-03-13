#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1000005;

int n, mod;

int fac[N], facd2[N], dfac[N];

void init()
{
  fac[0]   = 1;
  fac[1]   = 1;
  fac[2]   = 2;
  facd2[0] = 1;
  facd2[1] = 1;
  facd2[2] = 1;
  for (int i = 3; i <= n; i++)
  {
    fac[i]   = 1ll * fac[i - 1] * i % mod;
    facd2[i] = 1ll * facd2[i - 1] * i % mod;
  }

  dfac[n] = 1;
  for (int i = n - 1; i >= 1; i--)
    dfac[i] = 1ll * dfac[i + 1] * i % mod;
}

int main()
{
  n   = sc.next_int();
  mod = sc.next_int();

  init();

  int64_t ans = 0;

  for (int s = 1; s <= n; s++)
  {
    int64_t x00 = 1ll * (s - 1) * (s - 2) * 3 / 2;
    int64_t x10 = 1ll * (n - s) * (s - 1);
    ans += (x00 + x10) % mod * facd2[n - 1] % mod;

    int64_t x0 = s - 1;
    ans += x0 * fac[n - 1] % mod;

    int64_t y00 = 1ll * (n - s) * (n - s - 1) * 3 / 2;
    ans += y00 % mod * facd2[n - 1] % mod;
    int64_t y10 = 1ll * s * (n - s);
    ans += y10 % mod * fac[n - 1] % mod;
    int64_t y01 = 1ll * (n - 1) * s;
    ans += y01 % mod * fac[n - 1] % mod;

    int64_t z = 1ll * n * (n - 1);
    ans -= z % mod * dfac[n - s + 1] % mod;
  }

  ans = (ans % mod + mod) % mod;
  std::cout << ans << std::endl;

  return 0;
}
