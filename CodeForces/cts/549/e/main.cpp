#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#include <limits>

cm::scanner<cm::optimal_reader> sc(stdin);

struct point_t
{
  int x, y;
  constexpr point_t() : x(0), y(0) {}
  constexpr point_t(int x, int y) : x(x), y(y) {}
  
  constexpr point_t operator- (const point_t &rhs) const 
  { return point_t(x - rhs.x, y - rhs.y); }
  constexpr bool operator< (const point_t &rhs) const
  { return std::make_pair(x, y) < std::make_pair(rhs.x, rhs.y); }

  constexpr int dot(const point_t &rhs) const 
  { return x * rhs.x + y * rhs.y; }
  constexpr int cross(const point_t &rhs) const 
  { return x * rhs.y - y * rhs.x; }

  friend std::ostream& operator<< (std::ostream &out, point_t o) 
  {
    out << "(" << o.x << ", " << o.y << ")";
    return out;
  }
};

struct frac_t
{
  int x, y;
  constexpr frac_t() : x(0), y(1) {}
  constexpr frac_t(int x, int y) : x(y < 0 ? -x : x), y(y < 0 ? -y : y) {}

  constexpr bool operator< (const frac_t &rhs) const
  { return 1ll * x * rhs.y < 1ll * rhs.x * y; }
  
  constexpr static frac_t min() { return frac_t(-1000000000, 1); }
  constexpr static frac_t max() { return frac_t( 1000000000, 1); }

  friend std::ostream& operator<< (std::ostream &out, frac_t o) 
  {
    out << o.x << "/" << o.y;
    return out;
  }
};

constexpr int N = 10005;
point_t a[N], b[N];
int n, m;

int get_convex(point_t *o, const point_t *a, int n)
{
  point_t *cur = o;
  for (int i = 0; i < n; i++)
  {
    while (cur - o >= 2 && (cur[-1] - cur[-2]).cross(a[i] - cur[-1]) <= 0)
      cur --;
    *cur++ = a[i];
  }
  point_t *const but = cur - 1;
  for (int i = n - 2; i >= 0; i--)
  {
    while (cur - but >= 2 && (cur[-1] - cur[-2]).cross(a[i] - cur[-1]) <= 0)
      cur --;
    *cur++ = a[i];
  }
  cur--;
  return static_cast<int>(cur - o);
}

bool check_split(point_t x, point_t y, point_t *a, int n, point_t *b, int m)
{
  see(x, y);
  frac_t l = frac_t::min(); 
  frac_t r = frac_t::max();

  for (int i = 0; i < n; i++)
  {
    const point_t &o = a[i];
    const int c = (x - o).cross(y - o);
    const int d = (x - o).dot(y - o);
    if (c == 0) continue;
    const frac_t w(d, c);
    if ((y - x).cross(o - x) > 0) check_max(l, w);
    else check_min(r, w);
  }

  for (int i = 0; i < m; i++)
  {
    const point_t &o = b[i];
    const int c = (x - o).cross(y - o);
    const int d = (x - o).dot(y - o);
    if (c == 0)
    {
      if (d <= 0) return false;
      else continue;
    }
    const frac_t w(d, c);
    if ((y - x).cross(o - x) < 0) check_max(l, w);
    else check_min(r, w);
  }

  return l < r;
}

bool dfs_check(int l, int r, point_t *a, int n, point_t *b, int m)
{
  if (l + 1 == r) return false;
  frac_t max_r = frac_t::min();
  int max_id = l + 1;
  for (int i = l + 1; i < r; i ++)
  {
    const point_t &o = a[i];
    // see(o, a[l] - o, a[r] - o);
    const int c = (a[l] - o).cross(a[r] - o);
    const int d = (a[l] - o).dot(a[r] - o);
    const frac_t w(d, c);
    // see(c, d, w);
    if (check_max(max_r, w))
      max_id = i;
  }
  return check_split(a[l], a[max_id], a, n, b, m)
      || check_split(a[max_id], a[r], a, n, b, m)
      || dfs_check(l, max_id, a, n, b, m)
      || dfs_check(max_id, r, a, n, b, m);
}

bool check(point_t *a, int n, point_t *b, int m)
{
  static point_t c[N];
  n = get_convex(c, a, n);
  return check_split(c[0], c[n-1], c, n, b, m)
      || dfs_check(0, n-1, c, n, b, m);
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    a[i].x = sc.next_int();
    a[i].y = sc.next_int();
  }
  for (int i = 0; i < m; i++)
  {
    b[i].x = sc.next_int();
    b[i].y = sc.next_int();
  }

  if (n == 1 || m == 1) 
  {
    puts("YES");
    return 0;
  }

  std::sort(a, a + n);
  std::sort(b, b + m);

  if (check(a, n, b, m) || check(b, m, a, n))
    puts("YES");
  else
    puts("NO");
  return 0;
}

