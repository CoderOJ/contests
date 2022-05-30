#include <bits/stdc++.h>
#define LL long long
#define DB double
#define R int
#define G                                                                      \
  if (++ip == ie)                                                              \
    if (fread(ip = buf, 1, SZ, stdin))
using namespace std;
const int SZ = 1 << 19, N = 2e5 + 9;
char      buf[SZ], *ie = buf + SZ, *ip = ie - 1;
inline LL in()
{
  G;

  while (*ip < '-')
    G;

  LL x = *ip & 15;
  G;

  while (*ip > '-')
  {
    x *= 10;
    x += *ip & 15;
    G;
  }

  return x;
}
struct data_t
{
  int         d;
  LL          r;
  inline bool operator<(const data_t &a) const
  {
    return d < a.d;
  }
} a[N];
int        n, m, W, T, D, p = 1, st[N];
LL         X, b[N], c[N], f[N], y[N];
DB         k[N];
vector<LL> v[N];
inline DB  Slope(R i, R j)
{
  return (DB)(y[i] - y[j]) / (i - j);
}
int main()
{
  b[0] = X = in(), n = in(), m = in(), W = in(), T = in(), D = X % T;
  X /= T;

  for (R i = 1; i <= n; ++i)
    b[i] = in();

  for (R i = 1; i <= m; ++i)
    a[i].d = in(), a[i].r = in();

  sort(a + 1, a + m + 1);

  for (R i = 0; i <= n; ++i)
    v[lower_bound(a + 1, a + m + 1, (data_t){(int)(b[i] % T), 0}) - a - 1]
        .push_back(b[i] / T * W);

  for (R i = 1; i <= m; ++i)
  {
    c[i] = c[i - 1] + a[i].r;
    f[i] = f[i - 1] + (X + (a[i].d < D)) * W;

    for (auto x : v[i])
    {
      R j  = st[lower_bound(k + 1, k + p + 1, x) - k];
      f[i] = min(f[i], f[j] + c[i] - c[j] + x * (i - j));
    }

    y[i] = f[i] - c[i];

    while (p > 1 && k[p - 1] >= Slope(st[p - 1], i))
      --p;

    k[p]    = Slope(st[p], i);
    st[++p] = i;
    k[p]    = 9e18;
  }

  cout << f[m] + (X + 1) * W << endl;
  return 0;
}
