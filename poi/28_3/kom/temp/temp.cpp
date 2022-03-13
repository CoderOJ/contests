#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct point_t
{
  double x, y;
  double ans;
  double key;
  int    id;
};

int main()
{
  int n = sc.next_int();

  std::vector<point_t> a(n);
  for (int i = 0; i < n; i++)
  {
    a[i].x   = sc.next_double();
    a[i].y   = sc.next_double();
    a[i].ans = 0;
    a[i].id  = i;
  }

  const int T = 200;

  for (int _ = 0; _ < T; _++)
  {
    double ang     = M_PI / T * _;
    double ang_sin = std::sin(ang);
    double ang_cos = std::cos(ang);

    double sum = 0;
    for (auto &p : a)
    {
      p.key = p.x * ang_sin + p.y * ang_cos;
      sum += p.key;
    }

    std::sort(a.begin(), a.end(), [](const point_t &x, const point_t &y) {
      return x.key < y.key;
    });

    double prev = 0;
    double next = sum;
    for (int i = 0; i < n; i++)
    {
      a[i].ans += a[i].key * (i - (n - i)) - prev + next;
      prev += a[i].key;
      next -= a[i].key;
    }
  }

  const double ratio = M_PI / 2;
  for (auto &p : a)
    p.ans = p.ans / T * ratio;

  std::sort(a.begin(), a.end(), [](const point_t &x, const point_t &y) {
    return x.id < y.id;
  });

  for (auto &p : a)
    std::cout << p.ans << std::endl;

  return 0;
}
