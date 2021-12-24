#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr double eps = 1e-11;
constexpr int    N   = 1'000'005;

int    n;
double ans, sum, lstsum;

struct element_t
{
  int    p, t;
  double l, r;
} a[N];

bool equal(long double x, long double y)
{
  return std::abs(x - y) < eps;
}
bool compared(const element_t &u, const element_t &v)
{
  return 1.0L * u.p / u.t > 1.0L * v.p / v.t;
}
bool comparep(const element_t &u, const element_t &v)
{
  return u.p < v.p;
}

bool check(double mid)
{
  double max = -1e9;
  for (int i = 0, j; i < n; i = j)
  {
    for (j = i; j < n && a[i].p == a[j].p; j++)
      if (max > a[j].p * (1 - mid * a[j].r / sum))
        return false;
    for (j = i; j < n && a[i].p == a[j].p; j++)
      max = std::max(max, a[j].p * (1 - mid * a[j].l / sum));
  }
  return true;
}

int main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i].p = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i].t = sc.next_int();
  std::sort(a, a + n, compared);

  for (int i = 0, j; i < n; i = j)
  {
    lstsum = sum;
    for (j = i; j < n && equal(1.0L * a[i].p / a[i].t, 1.0L * a[j].p / a[j].t);
         j++)
      sum += a[j].t;
    for (j = i; j < n && equal(1.0L * a[i].p / a[i].t, 1.0L * a[j].p / a[j].t);
         j++)
    {
      a[j].l = lstsum + a[j].t;
      a[j].r = sum;
    }
  }

  std::sort(a, a + n, comparep);
  double l = 0, r = 1;
  for (int i = 0; i < 50; i++)
  {
    double mid = (l + r) / 2;
    if (check(mid))
    {
      l   = mid;
      ans = mid;
    }
    else
      r = mid;
  }
  printf("%.11f\n", ans);

  return 0;
}
