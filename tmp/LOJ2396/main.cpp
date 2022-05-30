#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstdint>
#include <limits>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 200005, 205)

struct node_t
{
  int64_t d;
  int64_t r;

  bool operator<(const node_t &a) const
  {
    return d < a.d;
  }
};

node_t a[N];

int64_t b[N], c[N], f[N], y[N];
int64_t t, x, d;
int     st[N], st_top = 1;
int     n, m, w;
double  k[N];

std::vector<int64_t> v[N];

double slope(int i, int j)
{
  return static_cast<double>(y[i] - y[j]) / (i - j);
}

int main()
{
  x = sc.next_long();
  n = sc.next_int();
  m = sc.next_int();
  w = sc.next_int();
  t = sc.next_long();

  b[0] = x;
  d    = x % t;
  x    = x / t;

  for (int i = 1; i <= n; ++i)
    b[i] = sc.next_long();
  for (int i = 1; i <= m; ++i)
  {
    a[i].d = sc.next_long();
    a[i].r = sc.next_long();
  }

  std::sort(a + 1, a + m + 1);

  for (int i = 0; i <= n; ++i)
  {
    size_t id = std::lower_bound(a + 1, a + m + 1, node_t{b[i] % t, 0}) - a - 1;
    v[id].push_back(b[i] / t * w);
  }

  st_top++;
  for (int i = 1; i <= m; ++i)
  {
    c[i] = c[i - 1] + a[i].r;
    f[i] = f[i - 1] + (x + (a[i].d < d)) * w;

    for (auto x : v[i])
    {
      int j = st[std::lower_bound(k + 1, k + st_top, x) - k];
      f[i]  = std::min(f[i], f[j] + c[i] - c[j] + x * (i - j));
    }

    y[i] = f[i] - c[i];

    while (st_top > 2 && k[st_top - 2] >= slope(st[st_top - 2], i))
      st_top--;

    k[st_top - 1] = slope(st[st_top - 1], i);
    st[st_top]    = i;
    k[st_top]     = std::numeric_limits<double>::max();
    st_top++;
  }

  std::cout << f[m] + (x + 1) * w << std::endl;

  return 0;
}