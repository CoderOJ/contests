#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <memory>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 30005;

struct point_t
{
  int x{}, y{};

  point_t() = default;
  point_t(int x, int y) : x(x), y(y) {}

  point_t operator+(const point_t &a) const
  {
    return {x + a.x, y + a.y};
  }

  point_t operator-(const point_t &a) const
  {
    return {x - a.x, y - a.y};
  }

  int64_t operator*(const point_t &a) const
  {
    return (int64_t)x * a.y - (int64_t)y * a.x;
  }

  int64_t operator^(const point_t &a) const
  {
    return (int64_t)x * a.x + (int64_t)y * a.y;
  }
};

point_t a[N], d[2];
int     n, m, dir[N];

std::vector<int> vec[N];

int main()
{
  n = sc.next_int();
  m = sc.next_int();

  for (int i = 1; i <= n; i++)
  {
    a[i].x = sc.next_int();
    a[i].y = sc.next_int();
    vec[sc.next_int()].push_back(i);
  }

  d[0].x = sc.next_int();
  d[0].y = sc.next_int();
  d[1].x = sc.next_int();
  d[1].y = sc.next_int();

  for (int i = 1; i <= n; i++)
  {
    if ((d[1] - a[i]) * (d[0] - a[i]) > 0)
      dir[i] = 1;
    else
      dir[i] = 0;
  }

  int q = sc.next_int();
  for (int i = 0; i < q; i++)
  {
    int x   = sc.next_int();
    int y   = sc.next_int();
    int ans = 0;

    for (auto u : vec[x])
      for (auto v : vec[y])
        if ((d[dir[u] ^ 1] - a[u]) * (a[v] - a[u]) < 0 &&
            (d[dir[u]] - a[u]) * (a[v] - a[u]) > 0)
          ans += 1;

    printf("%d\n", ans);
  }

  return (0 - 0);
}
