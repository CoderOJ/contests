#include <bits/stdc++.h>

template<class T, typename = typename T::iterator>
std::ostream &operator<< (std::ostream &out, const T& v)
{
  out << "{";
  bool first_time = true;
  for (const auto &i : v)
  {
    if (!first_time)
      out << ", ";
    first_time = false;
    out << i;
  }
  out << "}";
  return out;
}

constexpr int64_t operator ""_64(unsigned long long n)
{
  return static_cast<int64_t>(n);
}

struct point_t
{
  int x, y;
  explicit point_t(int x = 0, int y = 0) : x(x), y(y) {}
};

struct vector_t
{
  int x, y;
  explicit vector_t(int x = 0, int y = 0) : x(x), y(y) {}
  vector_t(point_t a, point_t b) : x(b.x - a.x), y(b.y - a.y) {}
};

double dis(const point_t &a, const point_t &b)
{
  return std::hypot(a.x - b.x, a.y - b.y);
}

double dot(const vector_t &a, const vector_t &b)
{
  return 1.0 * a.x * b.x + 1.0 * a.y * b.y;
}

double cross(const vector_t &a, const vector_t &b)
{
  return 1.0 * a.x * b.y - 1.0 * a.y * b.x;
}

double dis(const point_t &t, const point_t &a, const point_t &b)
{
  if (dot({a, t}, {a, b}) > 0 && dot({b, t}, {b, a}) > 0)
    return std::abs(cross({a, t}, {a, b})) / dis(a, b);
  else
    return std::min(dis(t, a), dis(t, b));
}

int main()
{
  int n, sx, sy;
  std::cin >> n >> sx >> sy;
  sx--, sy--;
  std::vector<point_t> p(n);
  for (int i = 0; i < n; i++)
    std::cin >> p[i].x >> p[i].y;
  std::vector<std::vector<std::pair<int, int>>> e(n);
  std::vector<std::pair<int, int>> es;
  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    e[u].emplace_back(v, i);
    e[v].emplace_back(u, i);
    es.emplace_back(u, v);
  }

  std::vector<std::vector<double>> d(n, std::vector<double>(n + n - 1));
  for (int i = 0; i < n; i++)
    for (int j = i; j < n; j++)
      d[i][j] = d[j][i] = dis(p[i], p[j]);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n - 1; j++)
      d[i][n + j] = dis(p[i], p[es[j].first], p[es[j].second]);

  // std::cout << "d = " << d << std::endl;

  std::vector<std::vector<double>> w(n, std::vector<double>(n + n - 1, std::numeric_limits<double>::max()));
  std::priority_queue<std::tuple<double, int, int>, std::vector<std::tuple<double, int, int>>, std::greater<std::tuple<double, int, int>>> que;
  w[sx][sy] = d[sx][sy];
  que.emplace(d[sx][sy], sx, sy);

  while (!que.empty())
  {
    const auto [ud, ux, uy] = que.top();
    que.pop();
    if (ud != w[ux][uy]) continue;
    // printf("extend: %d %d %lf %lf\n", ux, uy, ud, w[ux][uy]);

    if (uy < n)
    {
      for (const auto &[vy, vi] : e[uy])
      {
        double vd = std::max(ud, d[ux][n + vi]);
        if (vd < w[ux][n + vi])
        {
          w[ux][n + vi] = vd;
          que.emplace(vd, ux, n + vi);
        }
      }
      if (ud < w[uy][ux])
      {
        w[uy][ux] = ud;
        que.emplace(ud, uy, ux);
      }
    }
    else
    {
      for (const auto &[vy, vi] : e[ux])
      {
        double vd = std::max(ud, d[vy][uy]);
        if (vd < w[vy][uy])
        {
          w[vy][uy] = vd;
          que.emplace(vd, vy, uy);
        }
      }
      for (int vy : {es[uy - n].first, es[uy - n].second})
      {
        double vd = std::max(ud, d[ux][vy]);
        if (vd < w[ux][vy])
        {
          w[ux][vy] = vd;
          que.emplace(vd, ux, vy);
        }
      }
    }
  }

  double ans = std::numeric_limits<double>::max();
  for (int u = 0; u < n; u++)
    if (e[u].size() == 1)
      for (int v = 0; v < n; v++)
        if (e[v].size() == 1)
          ans = std::min(ans, w[u][v]);

  printf("%.12f\n", ans);

  return 0;
}
