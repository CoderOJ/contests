#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr long double eps  = 1e-9;
constexpr long double eeps = 1e-7;
constexpr int         N    = 100'005;
constexpr int         V    = 40'000'005;

std::pair<int, int> p[N];
long double         k, ox, oy, a[N], b[N], cx[N], cy[N];
long double         ans, dis[N], s[N], t[N], tb[N];
int                 n, m, q, rb[N], vol, stc[V];

struct FTree
{
  int f[N];

  void reset(int n)
  {
    memset(f, 0, (n + 1) * 4);
  }
  void modify(int u, int x)
  {
    for (int i = u; i <= m; i += i & -i)
    {
      f[i] += x;
    }
  }
  int query(int u)
  {
    int res = 0;
    for (int i = u; i >= 1; i ^= i & -i)
    {
      res += f[i];
    }
    return res;
  }
  int query(int l, int r)
  {
    if (l >= r)
    {
      return 0;
    }
    return query(r) - query(l);
  }
} tr;

long double get(int i, int j)
{
  long double x = (b[i] - b[j]) / (a[j] - a[i]), y = a[i] * x + b[i];
  return std::sqrt((x - ox) * (x - ox) + (y - oy) * (y - oy));
}

bool check(long double k, bool typ)
{
  int res = 0;
  m       = 0;
  for (int i = 0; i < n; i++)
  {
    long double x = cx[i] - ox, y = cy[i] - oy;
    if (dis[i] > k * k - eps)
    {
      continue;
    }
    if (std::abs(dis[i]) < eps)
    {
      s[i] = std::atan2(a[i], 1);
      t[i] = std::atan2(-a[i], -1);
    }
    else
    {
      long double z = std::sqrt(k * k / dis[i] - 1);
      s[i]          = std::atan2(y - x * z, x + y * z);
      t[i]          = std::atan2(y + x * z, x - y * z);
    }
    if (s[i] > t[i])
    {
      std::swap(s[i], t[i]);
    }
    s[i] += eps;
    t[i] -= eps;
    tb[m++] = s[i];
    tb[m++] = t[i];
  }
  std::sort(tb, tb + m);
  for (int i = 0; i < n; i++)
  {
    if (dis[i] > k * k - eps)
    {
      p[i] = {m, i};
      continue;
    }
    p[i]  = {std::upper_bound(tb, tb + m, s[i]) - tb - 1, i};
    rb[i] = static_cast<int>(std::upper_bound(tb, tb + m, t[i]) - tb);
  }
  std::sort(p, p + n);
  if (!typ)
  {
    tr.reset(m);
    for (int i = 0; i < n; i++)
    {
      if (p[i].first == m)
      {
        break;
      }
      res += tr.query(p[i].first, rb[p[i].second]);
      tr.modify(rb[p[i].second], 1);
      if (res >= q)
      {
        return false;
      }
    }
  }
  else
  {
    for (int i = 0; i < n; i++)
    {
      if (p[i].first == m)
        break;

      while (vol > 0 && rb[stc[vol]] <= p[i].first)
        vol--;
      stc[++vol] = p[i].second;
      for (int i = vol - 1; i > 0; i--)
      {
        if (rb[stc[i]] > rb[stc[i + 1]])
          break;
        long double tmp = get(stc[i], stc[i + 1]);
        ans += tmp;
        res++;
        std::swap(stc[i], stc[i + 1]);
      }
    }
    ans += (q - res) * k;
  }
  return true;
}

int main()
{
  n  = sc.next_int();
  ox = sc.next_int() / 1000.0;
  oy = sc.next_int() / 1000.0;
  q  = sc.next_int();

  int pass = 0;
  for (int i = 0; i < n; i++)
  {
    a[i] = sc.next_int() / 1000.0;
    b[i] = sc.next_int() / 1000.0;
    if (std::abs(a[i]) < eps)
    {
      cx[i] = ox;
      cy[i] = b[i];
    }
    else
    {
      long double _a = -1 / a[i], _b = oy - _a * ox;
      cx[i] = (_b - b[i]) / (a[i] - _a);
      cy[i] = a[i] * cx[i] + b[i];
    }
    dis[i] = (ox - cx[i]) * (ox - cx[i]) + (oy - cy[i]) * (oy - cy[i]);
    if (dis[i] < eps)
    {
      pass++;
    }
  }

  if (pass * (pass - 1ll) / 2 >= q)
  {
    printf("0.000000\n");
  }
  else
  {
    for (long double l = eeps, r = 21e8, mid; l <= r;)
    {
      mid = (l + r) / 2;
      if (check(mid, false))
      {
        l = mid + eeps;
        k = mid;
      }
      else
      {
        r = mid - eeps;
      }
    }
    check(k, true);
    printf("%.10f\n", static_cast<double>(ans));
  }
  return 0;
}
