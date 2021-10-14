
#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#include <cmath>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int V = 100000;
constexpr int N = 100005;

struct point
{
  int x, y;
  point(int x = 0, int y = 0) : x(x), y(y)
  {
  }
  friend point operator-(point a, point b)
  {
    return point(a.x - b.x, a.y - b.y);
  }
  friend long long operator/(point a, point b)
  {
    return (long long)a.x * b.y - (long long)a.y * b.x;
  }
  long long len()
  {
    return (long long)x * x + (long long)y * y;
  }
  bool operator== (const point &rhs) const 
  {
    return x == rhs.x && y == rhs.y;
  }
  friend std::ostream& operator<< (std::ostream& out, point x)
  {
    out << x.x << " " << x.y;
    return out;
  }
};

int n, cnt, top;
point p[N * 6];
void push(int x, int y)
{
  p[++cnt] = point(x, y);
}
point c[N * 6];

int main()
{
  n = sc.next_int();
  for (int i = 1; i <= n; ++i)
  {
    int x = sc.next_int();
    int y = sc.next_int();
    int v = sc.next_int();
    if (x < v)
      push(0, std::max(y - v + x, 0)), push(0, std::min(y + v - x, V));
    else
      push(x - v, y);
    if (y < v)
      push(std::max(x - v + y, 0), 0), push(std::min(x + v - y, V), 0);
    else
      push(x, y - v);
    if (x > V - v)
      push(V, std::max(y - x - v + V, 0)), push(V, std::min(y + x + v - V, V));
    else
      push(x + v, y);
    if (y > V - v)
      push(std::max(x - y - v + V, 0), V), push(std::min(x + y + v - V, V), V);
    else
      push(x, y + v);
  }

  std::sort(p + 1, p + cnt + 1, [](point a, point b) {
    return a.y == b.y ? a.x < b.x : a.y < b.y;
  });
  cnt = static_cast<int>(std::unique(p + 1, p + cnt + 1) - p - 1);
  std::sort(p + 2, p + cnt + 1, [](point a, point b) {
    long long cr = (a - p[1]) / (b - p[1]);
    return cr == 0 ? (a - p[1]).len() < (b - p[1]).len() : cr > 0;
  });

  c[1] = p[1], c[top = 2] = p[2];
  for (int i = 3; i <= cnt; ++i)
  {
    while (top > 1 && (p[i] - c[top - 1]) / (c[top] - c[top - 1]) >= 0)
      --top;
    c[++top] = p[i];
  }
  c[0] = c[top], c[top + 1] = c[1];
  
  double ans = 0;
  int a = 0;
  for (int i = 1; i <= top; ++i)
  {
    point x = c[i - 1] - c[i], y = c[i + 1] - c[i], z = c[i + 1] - c[i - 1];
    double rad = std::sqrt(x.len()) * std::sqrt(y.len()) * std::sqrt(z.len()) /
                 static_cast<double>((y / x * 2));
    if (rad > ans)
      ans = rad, a = i;
  }
  std::cout << c[a - 1] << std::endl << c[a] << std::endl << c[a + 1] << std::endl;
  return 0;
}
