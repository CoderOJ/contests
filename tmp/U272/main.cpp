#include <bits/stdc++.h>

#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; ++i)

using u64 = unsigned long long;
using u32 = unsigned int;

const int N = 531441;
const int M = 15;

int n, m, t, mod, inv_n;

int pow(int a, int b, int ans = 1)
{
  for (; b; b >>= 1, a = (u64)a * a % mod)
    if (b & 1)
      ans = (u64)ans * a % mod;
  return ans;
}

std::vector<int> d;

int getphi(int x)
{
  int o = x;
  for (int i = 2; i * i <= x; ++i)
  {
    if (x % i == 0)
    {
      o /= i, o *= i - 1;
      do
        x /= i;
      while (x % i == 0);
    }
  }
  if (x > 1)
    o /= x, o *= x - 1;
  return o;
}

void factor(int x)
{
  for (int i = 2; i * i <= x; ++i)
  {
    if (x % i == 0)
    {
      do
        x /= i, d.push_back(i);
      while (x % i == 0);
    }
  }
  if (x > 1)
    d.push_back(x);
}

int getg()
{
  std::mt19937 gen;
  int          p = getphi(mod);
  inv_n          = pow(n, p - 1);
  factor(p);
  d.erase(find(d.begin(), d.end(), 3));
  for (;;)
  {
    int x = gen() % (mod - 1) + 1;
    if (std::__gcd(x, mod) != 1)
      continue;
    int z = p;
    for (int o : d)
    {
      const int p = pow(x, z / o);
      if (p == 1)
        z /= o;
    }
    x = pow(x, z / 3);
    if (x != 1 && std::gcd(x - 1, mod) == 1)
    {
      return x;
    }
  }
}

int popc1[N];
int popc2[N];
int f[N], g[N];
int b[M][M];

int G[3];

void dft(int &a, int &b, int &c)
{
  int x = a, y = b, z = c;
  a = ((u32)x + y + z) % mod;
  b = (x + (u64)G[1] * y + (u64)G[2] * z) % mod;
  c = (x + (u64)G[2] * y + (u64)G[1] * z) % mod;
}

void idft(int &a, int &b, int &c)
{
  int x = a, y = b, z = c;
  a = ((u32)x + y + z) % mod;
  b = (x + (u64)G[2] * y + (u64)G[1] * z) % mod;
  c = (x + (u64)G[1] * y + (u64)G[2] * z) % mod;
}

void fwt(int a[])
{
  for (int i = 1; i < n; i *= 3)
    for (int j = 0; j < n; j += i * 3)
      for (int k = 0; k < i; ++k)
        dft(a[j + k], a[j + k + i], a[j + k + i + i]);
}

void ifwt(int a[])
{
  for (int i = 1; i < n; i *= 3)
    for (int j = 0; j < n; j += i * 3)
      for (int k = 0; k < i; ++k)
        idft(a[j + k], a[j + k + i], a[j + k + i + i]);
  for (int i = 0; i < n; ++i)
    a[i] = (u64)a[i] * inv_n % mod;
}

int main()
{
  scanf("%d%d%d", &m, &t, &mod);
  n = 1;
  for (int i = 0; i < m; ++i)
    n *= 3;

  for (int i = 1; i < n; ++i)
  {
    popc1[i] = popc1[i / 3] + (i % 3 == 1);
    popc2[i] = popc2[i / 3] + (i % 3 == 2);
  }

  if (mod == 1)
  {
    for (int i = 0; i < n; ++i)
      puts("0");
    return 0;
  }

  for (int i = 0; i < n; ++i)
    scanf("%d", &f[i]);
  for (int i = 0; i <= m; ++i)
    for (int j = 0; i + j <= m; ++j)
      scanf("%d", &b[i][j]);

  G[0] = 1, G[1] = getg(), G[2] = (u64)G[1] * G[1] % mod;
  for (int i = 0; i < n; ++i)
    g[i] = b[popc1[i]][popc2[i]];

  fwt(f);
  fwt(g);
  for (int i = 0; i < n; ++i)
    f[i] = pow(g[i], t, f[i]);
  ifwt(f);

  for (int i = 0; i < n; ++i)
    printf("%d\n", f[i]);
}
