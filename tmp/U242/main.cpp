#include <bits/stdc++.h>

const int N = 100005;

int n;

struct angle_t
{
  int x, y;
  angle_t(int x = 0, int y = 0) : x(x), y(y) {}

  angle_t reverse()
  {
    return {-x, -y};
  }

  int64_t operator*(const angle_t &rhs) const
  {
    return (int64_t)x * rhs.y - (int64_t)y * rhs.x;
  }

  bool neg() const
  {
    return y < 0 || (y == 0 && x < 0);
  }

  bool operator<(const angle_t &rhs) const
  {
    if (neg() != rhs.neg())
      return neg() > rhs.neg();
    return *this * rhs > 0;
  }

  bool operator==(const angle_t &rhs) const
  {
    return x == rhs.x && y == rhs.y;
  }
};

angle_t a[N];

angle_t make_angle(const int &x, const int &y)
{
  int g = std::gcd(x, y);
  if (g < 0)
    return {-x / g, -y / g};
  else
    return {x / g, y / g};
}

struct point_t
{
  double x, y;
  point_t(double x = 0, double y = 0) : x(x), y(y) {}

  bool operator<(const point_t &rhs) const
  {
    return x == rhs.x ? y < rhs.y : x < rhs.x;
  }

  point_t operator+(const point_t &rhs) const
  {
    return {x + rhs.x, y + rhs.y};
  }

  point_t operator-(const point_t &rhs) const
  {
    return {x - rhs.x, y - rhs.y};
  }

  point_t operator*(const double &rhs) const
  {
    return {x * rhs, y * rhs};
  }

  double operator*(const point_t &rhs) const
  {
    return x * rhs.y - y * rhs.x;
  }

  point_t reverse() const
  {
    return {-x, -y};
  }
};

struct line
{
  point_t p, v;
  line() = default;
  line(const point_t &a, const point_t &b) : p(a), v(b - a) {}

  line reverse()
  {
    return {p + v, p};
  }
};

line s[N], l;

point_t cross(const line &a, const line &b)
{
  return b.p + b.v * ((b.p - a.p) * a.v / (a.v * b.v));
}

std::vector<std::pair<point_t, int>> ins;
std::multiset<angle_t>               ss;
int                                  s_cnt;

int check(angle_t a, angle_t b, int flag = 0)
{
  if (a == b)
    return flag;
  else if (a.reverse() == b)
    return 1;
  else
    return a * b < 0;
}

void ss_insert(const angle_t &c)
{
  std::multiset<angle_t>::iterator pre, nex, it;

  bool fpre = false, fnex = false;
  pre = nex = it = ss.insert(c);
  if (pre == ss.begin())
  {
    pre  = std::prev(ss.end());
    fpre = true;
  }
  else
    pre--;

  if (++nex == ss.end())
  {
    nex  = ss.begin();
    fnex = true;
  }
  s_cnt += check(*pre, *it, fpre) + check(*it, *nex, fnex) -
           check(*pre, *nex, fpre || fnex);
}

void ss_erase(const angle_t &c)
{
  std::multiset<angle_t>::iterator pre, nex, it;

  bool fpre = false, fnex = false;
  pre = nex = it = ss.find(c);
  if (pre == ss.begin())
  {
    pre  = std::prev(ss.end());
    fpre = true;
  }
  else
    pre--;

  if (++nex == ss.end())
  {
    nex  = ss.begin();
    fnex = true;
  }
  s_cnt += check(*pre, *nex, fpre || fnex) - check(*pre, *it, fpre) -
           check(*it, *nex, fnex);

  ss.erase(it);
}

void init()
{
  scanf("%d", &n);
  for (int i = 0; i <= n; i++)
  {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    s[i] = line(point_t(x1, y1), point_t(x2, y2));
    a[i] = make_angle(x2 - x1, y2 - y1);
  }
  std::swap(s[n], l);

  for (int i = 0; i < n; i++)
  {
    if (l.v * s[i].v < 0)
    {
      s[i] = s[i].reverse();
      a[i] = a[i].reverse();
    }
    ins.emplace_back(cross(s[i], l), i);
    ss_insert(a[i]);
  }

  std::sort(ins.begin(), ins.end());
  std::multiset<angle_t>::iterator it0, it1;
  s_cnt = check(*ss.rbegin(), *ss.begin(), true);
  for (it0 = ss.begin(), it1 = std::next(it0); it1 != ss.end(); it0++, it1++)
    s_cnt += check(*it0, *it1);
}

void solve()
{
  for (auto &in : ins)
  {
    putchar(s_cnt == 0 ? '1' : '0');
    int k = in.second;
    ss_erase(a[k]);
    a[k] = a[k].reverse();
    ss_insert(a[k]);
  }
  putchar(s_cnt == 0 ? '1' : '0');
  puts("");
}

int main()
{
  init();
  solve();
  return 0;
}
