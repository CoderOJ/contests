#include <bits/stdc++.h>

int64_t operator""_64(unsigned long long x)
{
  return static_cast<int64_t>(x);
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

struct frac_t
{
  int64_t a, b;
  frac_t(int64_t a = 0, int64_t b = 1) : a(a), b(b) {}

  bool operator<(frac_t rhs) const
  {
    return __int128_t(a) * rhs.b < __int128_t(rhs.a) * b;
  }

  frac_t operator-() const
  {
    return {-a, b};
  }
};

int64_t dot(vector_t a, vector_t b)
{
  return 1_64 * a.x * b.x + 1_64 * a.y * b.y;
}

int64_t cross(vector_t a, vector_t b)
{
  return 1_64 * a.x * b.y - 1_64 * a.y * b.x;
}

frac_t cross_dis(point_t aa, point_t ab, point_t b, vector_t vb)
{
  int64_t ra = cross({b, aa}, vb);
  int64_t rb = cross(vb, {b, ab});
  return {ra, ra + rb};
}

std::ostream& operator<<(std::ostream &out, frac_t f)
{
  return out << f.a << "/" << f.b;
  // return out << 1.0 * f.a / f.b;
}

template <class T, typename = typename T::iterator>
std::ostream &operator<<(std::ostream &out, const T &v)
{
  out << "{";
  bool is_first = true;
  for (const auto &x : v)
  {
    if (!is_first) out << ", ";
    else is_first = false;
    out << x;
  }
  out << "}";
  return out;
}

const int N = 100005;

point_t a[N], b[N];
int n;

std::vector<int> check(const std::vector<int> &v)
{
  // std::cout << "check: v = " << v << std::endl;
  std::vector<int> res(v.size());
  std::vector<std::pair<int, size_t>> st;
  for (size_t i = 0; i < v.size(); i++)
  {
    if (st.empty() || st.back().first < v[i])
      st.emplace_back(v[i], i);
    else
    {
      auto l = std::upper_bound(st.begin(), st.end(), std::make_pair(v[i], i));
      if (l != st.end())
      {
        res[l->second]++;
        res[i]--;
      }
    }
  }
  std::partial_sum(res.begin(), res.end(), res.begin());
  // std::cout << res << std::endl;
  return res;
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i <= n; i++)
  {
    scanf("%d%d", &a[i].x, &a[i].y);
    scanf("%d%d", &b[i].x, &b[i].y);
  }
  point_t sa = a[n], sb = b[n];
  vector_t s(sa, sb);

  auto ang_cmp = [](vector_t a, vector_t b) {
    return cross(a, b) < 0;
  };
  auto ang_eq = [](vector_t a, vector_t b) {
    return cross(a, b) == 0;
  };
  std::vector<vector_t> vs;

  for (int i = 0; i < n; i++)
  {
    if (cross(s, {a[i], b[i]}) < 0)
      std::swap(a[i], b[i]);
    vs.emplace_back(a[i], b[i]);
  }
  std::sort(vs.begin(), vs.end(), ang_cmp);
  vs.erase(std::unique(vs.begin(), vs.end(), ang_eq), vs.end());

  std::vector<std::pair<frac_t, int>> v;
  for (int i = 0; i < n; i++)
  {
    frac_t d = cross_dis(sa, sb, a[i], {a[i], b[i]});
    int r = static_cast<int>(std::lower_bound(vs.begin(), vs.end(), vector_t(a[i], b[i]), ang_cmp) - vs.begin());
    v.emplace_back(d, r);
  }
  std::sort(v.begin(), v.end());

  auto a0 = [&]{
    std::vector<int> f;
    for (int i = 0; i < n; i++)
      f.push_back(v[i].second);
    return check(f);
  }();
  auto a1 = [&]{
    std::vector<int> f;
    for (int i = 0; i < n; i++)
      f.push_back(-v[i].second);
    return check(f);
  }();

  putchar('0');
  for (int i = 0; i < n; i++)
    putchar((a0[i] && a1[i]) ? '1' : '0');
  puts("");

  return 0;
}
