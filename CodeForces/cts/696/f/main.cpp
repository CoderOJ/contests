#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cmath>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr long double eeps = 1e-16L;
constexpr long double eps  = 1e-14L;
constexpr long double inf  = 1e18;

struct point_t
{
  long double x, y;

  [[nodiscard]] long double length() const
  {
    return std::sqrt(x * x + y * y);
  }
};

bool operator<(const point_t &u, const point_t &v)
{
  return std::abs(u.x - v.x) < eeps ? u.y < v.y : u.x < v.x;
}
point_t operator~(const point_t &u)
{
  return (point_t){-u.y, u.x};
}
point_t operator-(const point_t &u)
{
  return (point_t){-u.x, -u.y};
}
point_t operator*(const point_t &u, long double k)
{
  return (point_t){u.x * k, u.y * k};
}
point_t operator/(const point_t &u, long double k)
{
  return (point_t){u.x / k, u.y / k};
}
point_t operator+(const point_t &u, const point_t &v)
{
  return (point_t){u.x + v.x, u.y + v.y};
}
point_t operator-(const point_t &u, const point_t &v)
{
  return (point_t){u.x - v.x, u.y - v.y};
}
point_t operator>>(const point_t &u, const point_t &v)
{
  return (point_t){v.x - u.x, v.y - u.y};
}
long double operator*(const point_t &u, const point_t &v)
{
  return u.x * v.x + u.y * v.y;
}
long double operator^(const point_t &u, const point_t &v)
{
  return u.x * v.y - u.y * v.x;
}

struct line_t
{
  point_t     s, t;
  long double arg, dis;

  line_t(point_t u, point_t v)
  {
    s   = u;
    t   = v;
    arg = std::atan2((s >> t).y, (s >> t).x);
    dis = (s ^ t) / (s >> t).length();
  }

  bool contain(point_t u)
  {
    return ((s >> t) ^ (s >> u)) > -eps;
  }
};

bool operator<(const line_t &a, const line_t &b)
{
  return std::abs(a.arg - b.arg) < eps ? a.dis < b.dis : a.arg < b.arg;
}
point_t operator&(const line_t &a, const line_t &b)
{
  point_t u = a.s >> a.t, v = b.s >> b.t, w = a.s >> b.s;
  if (std::abs(u ^ v) < eeps)
    return (point_t){-inf, -inf};
  return a.s + u * ((w ^ v) / (u ^ v));
}

std::vector<line_t> intersection(std::vector<line_t> a)
{
  std::sort(a.begin(), a.end());
  int                 l = 0, r = -1;
  std::vector<line_t> que = a;
  for (int i = 0; i < (int)a.size(); i++)
  {
    if (i > 0 && std::abs(a[i - 1].arg - a[i].arg) < eps)
      continue;
    for (; l < r && !a[i].contain(que[r] & que[r - 1]); r--)
      ;
    for (; l < r && !a[i].contain(que[l] & que[l + 1]); l++)
      ;
    que[++r] = a[i];
  }
  for (; l < r && !que[l].contain(que[r] & que[r - 1]); r--)
    ;
  for (; l < r && !que[r].contain(que[l] & que[l + 1]); l++)
    ;
  a.assign(que.begin() + l, que.begin() + r + 1);
  return a;
}

const int N = 305;

int     n;
point_t p[N], q[N], s, t;

struct element_t
{
  line_t a;
  int    i;
};

std::vector<element_t> e;

bool operator<(const element_t &x, const element_t &y)
{
  return x.a < y.a;
}

std::vector<line_t> get(int i, int j, int o)
{
  std::vector<line_t> a;
  if (o == 0)
  {
    for (auto k : e)
      if (k.i == -1 || (i <= k.i && k.i < j))
        a.push_back(k.a);
  }
  else
  {
    for (auto k : e)
      if (k.i == -1 || (k.i < i || j <= k.i))
        a.push_back(k.a);
  }
  return intersection(a);
}

bool check(long double mid)
{
  e.clear();
  for (int i = 0; i < n; i++)
  {
    int j = (i + 1) % n;
    e.push_back((element_t){line_t(p[i], p[j]), -1});
    e.push_back((element_t){line_t(p[j] + q[i] * mid, p[i] + q[i] * mid), i});
  }
  std::sort(e.begin(), e.end());
  std::vector<line_t> a, b;
  for (int i = 0, j = 0; i < n && j < n; i++)
  {
    for (; j < n; j++)
    {
      if (get(i, j + 1, 0).size() <= 2)
      {
        break;
      }
    }
    a = get(i, j, 1);
    if (a.size() > 2)
    {
      b = get(i, j, 0);
      s = a[0] & a[1];
      t = b[0] & b[1];
      return true;
    }
  }
  return false;
}

int main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    p[i].x = sc.next_int();
    p[i].y = sc.next_int();
  }
  for (int i = 0; i < n; i++)
  {
    q[i] = ~(p[i] >> p[(i + 1) % n]);
    q[i] = q[i] / q[i].length();
  }

  long double l = 0, r = 2e4;
  for (int i = 0; i <= 50; i++)
  {
    long double mid = (l + r) / 2;
    if (check(mid))
      r = mid;
    else
      l = mid;
  }

  check(l);
  printf("%.12Lf\n", l);
  printf("%.12Lf %.12Lf\n", s.x, s.y);
  printf("%.12Lf %.12Lf\n", t.x, t.y);

  return 0;
}
