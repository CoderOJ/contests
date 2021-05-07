#include <stdio.h>

#define L(i, j, k) for (int i = (j); i <= (k); i++)
#define R(i, j, k) for (int i = (j); i >= (k); i--)

#define N 1000007
#define mod 998244353

int n, k, x, pk, f[N], pw1[N], pw2[N], ns;
int fac[N], ifac[N], inv[N];

void init(int x)
{
  fac[0] = ifac[0] = inv[1] = 1;
  L(i, 2, x) inv[i] = (long long)inv[mod % i] * (mod - mod / i) % mod;
  L(i, 1, x) fac[i] = (long long)fac[i - 1] * i % mod, ifac[i] = (long long)ifac[i - 1] * inv[i] % mod;
}

int C(int x, int y)
{
  if (y < 0 || x < y)
    return 0;
  return 1ll * fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}

int get(int d, int n)
{
  if (n < 0)
    return 0;
  int res = 0;
  L(g, 0, n / d)
  {
    res += 1ll * C(g + (n - d * g), g) 
               * pw1[n - d * g]        % mod 
               * pw2[g]                % mod;
    res %= mod;
  }
  return res;
}

int main()
{
  scanf("%d%d%d", &n, &k, &x);
  pk = (mod + 1 - k) % mod, init(n);
  pw1[0] = pw2[0] = 1;

  L(i, 1, n) 
  {
    pw1[i] = 1ll * pw1[i - 1] * k % mod;
    pw2[i] = 1ll * pw2[i - 1] * pk % mod;
  }
  L(i, 1, n) 
    f[i] = (get(i + 1, n - 1) + mod - get(i + 1, n - i - 1)) % mod;

  L(i, x + 1, n)
  {
    ns += 1ll * (f[i] + mod - f[i - 1]) * (i - x) % mod;
    ns %= mod;
  }

  ns = 1ll * ns * k % mod;
  printf("%d\n", ns);
  return 0;
}
