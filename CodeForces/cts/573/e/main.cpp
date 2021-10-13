#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#include <cmath>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 100'005;
constexpr int M = 370;
const double inf = 1e18L;
int n, m, k, a[N], b[N], p[N], l[M], r[M];
long long f[N], ans;

struct block_t
{
  int l, r, q[M];
  long long k, b;
  inline long long c(int i)
  {
    return f[i] + k * a[i] + b;
  }
  inline double s(int i, int j)
  {
    if (a[i] == a[j])
      return f[i] > f[j] ? -inf : inf;
    return static_cast<double>(f[i] - f[j]) / static_cast<double>(a[i] - a[j]);
  }
  inline void buidouble(int x)
  {
    for (int i = ::l[x]; i <= ::r[x]; i++)
      f[i] += k * a[i] + b;
    k = b = l = r = 0;
    for (int i = ::l[x]; i <= ::r[x]; i++)
    {
      while (r - l > 1 && s(q[r - 2], q[r - 1]) < s(q[r - 1], p[i]))
        --r;
      q[r++] = p[i];
    }
  }
  inline std::pair<long long, int> ask()
  {
    while (r - l > 1 && c(q[l]) <= c(q[l + 1]))
      ++l;
    return std::make_pair(c(q[l]), q[l]);
  }
} t[M];

int main()
{
  n = sc.next_int();
  m = static_cast<int>(std::sqrt(n));
  for (int i = k = 1; i <= n; k += !(i % m), i++)
  {
    a[i] = sc.next_int();
    f[i] = a[i];
    p[i] = i;
    b[i] = k;
  }
  if (!(n % m))
    --k;
  for (int i = 1; i <= k; i++)
  {
    l[i] = r[i - 1] + 1, r[i] = std::min(i * m, n);
    std::sort(p + l[i], p + r[i] + 1,
              [&](int i, int j) { return a[i] < a[j]; });
    t[i].buidouble(i);
  }
  while (1)
  {
    std::pair<long long, int> o = std::make_pair(0, 0);
    for (int i = 1; i <= k; i++)
      o = max(o, t[i].ask());
    if (!o.first)
    {
      printf("%lld\n", ans);
      return 0;
    }
    ans += o.first, f[o.second] = -1e18;
    for (int i = 1; i < b[o.second]; i++)
      t[i].b += a[o.second];
    for (int i = l[b[o.second]]; i < o.second; i++)
      f[i] += a[o.second];
    for (int i = o.second + 1; i <= r[b[o.second]]; i++)
      f[i] += a[i];
    for (int i = b[o.second] + 1; i <= k; i++)
      ++t[i].k;
    t[b[o.second]].buidouble(b[o.second]);
  }
  return 0;
}
