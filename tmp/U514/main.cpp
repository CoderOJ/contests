#include <bits/stdc++.h>

const int MOD = 998244353;
const int N = 256;
const int M = N * N;

auto [fac, inv, ifac] = []{
  std::array<int, M> fac, inv, ifac;
  fac[0] = inv[0] = ifac[0] = 1;
  fac[1] = inv[1] = ifac[1] = 1;
  for (int i = 2; i < M; i++)
  {
    fac[i] = 1ll * fac[i - 1] * i % MOD;
    inv[i] = 1ll * inv[MOD % i] * (MOD - MOD / i) % MOD;
    ifac[i] = 1ll * ifac[i - 1] * inv[i] % MOD;
  }
  return std::make_tuple(fac, inv, ifac);
}();

int power(int a, int b)
{
  int r = 1;
  for (; b; b >>= 1)
  {
    if (b & 1) r = 1ll * a * r % MOD;
    a = 1ll * a * a % MOD;
  }
  return r;
}

namespace ntt
{

const int N = 16;
const int L = 1 << N;

auto w = []{
  std::array<int, L> w;
  for (int i = 1; i < L; i <<= 1)
  {
    int cw = power(3, (MOD - 1) / i / 2);
    w[i] = 1;
    for (int j = 1; j < i; j++)
      w[i + j] = 1ll * w[i + j - 1] * cw % MOD;
  }
  return w;
}();

void butterfly(int a[])
{
  static auto rev = []{
    std::array<uint32_t, L> rev;
    for (int i = 1; i < L; i++)
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (N - 1));
    return rev;
  }();
  for (int i = 0; i < L; i++)
    if ((int)rev[i] < i)
      std::swap(a[i], a[rev[i]]);
}

void dft(int a[])
{
  butterfly(a);
  for (int i = 1; i < L; i <<= 1)
    for (int j = 0; j < L; j += 2 * i)
      for (int k = 0; k < i; k++)
      {
        int cw = w[i + k];
        int x = a[j + k];
        int y = a[j + i + k];
        a[j + k] = (x + 1ll * cw * y) % MOD;
        a[j + i + k] = (x - 1ll * cw * y) % MOD;
      }
  for (int i = 0; i < L; i++)
    if (a[i] < 0)
      a[i] += MOD;
}

void idft(int a[])
{
  static int inv_l = power(L, MOD - 2);
  std::reverse(a + 1, a + L);
  dft(a);
  for (int i = 0; i < L; i++)
    a[i] = 1ll * a[i] * inv_l % MOD;
}

}

auto [n, a, b] = []{
  int n, a, b;
  scanf("%d%d%d", &n, &a, &b);
  return std::make_tuple(n, a, b);
}();

auto ans = []{
  static int fi[M], f[M], g[M];

  for (int i = 0; i < b; i++) 
    fi[i] = ifac[i];
  ntt::dft(fi);

  int ans = 0;
  for (int i = 0; i < M; i++)
    f[i] = 1;
  for (int i = 1; i < n; i++)
  {
    for (int i = 0; i < M; i++)
      f[i] = 1ll * f[i] * fi[i] % MOD;
    std::copy(f, f + M, g);
    ntt::idft(g);

    int cur_ans = 0;
    int inv_i = power(i + 1, MOD - 2);
    int ipow_i = power(inv_i, a);
    for (int j = 0; j <= i * (b - 1); j++)
    {
      int c = 1ll * g[j] * ifac[a - 1] % MOD * fac[j + a - 1] % MOD;
      // printf("%d: %d: c = %d\n", i, j, c);
      cur_ans = (cur_ans + 1ll * c * ipow_i) % MOD;
      ipow_i = 1ll * ipow_i * inv_i % MOD;
    }
    int cur_binom = 1ll * fac[n - 1] * ifac[i] % MOD * ifac[n - 1 - i] % MOD;

    if (i % 2 == 1)
      ans = (ans + 1ll * cur_ans * cur_binom) % MOD;
    else
      ans = (ans - 1ll * cur_ans * cur_binom) % MOD;
  }

  ans = 1ll * ans * n % MOD;
  if (ans < 0) ans += MOD;
  return ans;
}();


int main()
{
  printf("%d\n", ans);
  return 0;
}
