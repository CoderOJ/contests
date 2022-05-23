#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <limits>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

const int N = 100005;

struct point_t
{
  int x, y;
};

struct line_t
{
  int64_t x, y, c;

  line_t() = default;
  line_t(point_t a, point_t b) :
      x(a.y - b.y), y(b.x - a.x), c(-(x * a.x + y * a.y))
  {
  }

  int64_t eval(point_t p) const
  {
    return x * p.x + y * p.y + c;
  }
};

std::ostream &operator<<(std::ostream &out, point_t p)
{
  return out << "(" << p.x << ", " << p.y << ")";
}

struct sgt_t
{
  struct node_t
  {
    std::vector<point_t>           a;
    std::vector<point_t>::iterator p;

    void push_up(const node_t &lhs, const node_t &rhs)
    {
      a = lhs.a;
      for (point_t c : rhs.a)
      {
        while (a.size() >= 2)
        {
          int64_t ddx = a[a.size() - 1].x - a[a.size() - 2].x;
          int64_t ddy = a[a.size() - 1].y - a[a.size() - 2].y;
          int64_t dx  = c.x - a[a.size() - 1].x;
          int64_t dy  = c.y - a[a.size() - 1].y;
          if (ddx * dy - ddy * dx >= 0)
            a.pop_back();
          else
            break;
        }
        a.push_back(c);
      }
      p = a.begin();
    }

    int64_t query(const line_t &l)
    {
      if (a.empty())
        return std::numeric_limits<int64_t>::min();
      while (std::next(p) != a.end() && l.eval(*std::next(p)) >= l.eval(*p))
        p++;
      return l.eval(*p);
    }
  };

  node_t p[N * 4];

  void build(int u, int l, int r, point_t a[])
  {
    if (r - l == 1)
    {
      p[u].a = {a[l]};
      p[u].p = p[u].a.begin();
    }
    else
    {
      int m = l + (r - l) / 2;
      build(u + u, l, m, a);
      build(u + u + 1, m, r, a);
      p[u].push_up(p[u + u], p[u + u + 1]);
    }
  }

  int find(int u, int l, int r, int ql, int qr, const line_t &line)
  {
    // see("find", u, l, r, ql, qr);
    if (ql <= l && r <= qr)
    {
      bool f = p[u].query(line) > 0;
      if (!f)
        return r;
      else
      {
        if (r - 1 == l)
          return l;
        else
        {
          int m     = l + (r - l) / 2;
          int l_res = find(u + u, l, m, ql, qr, line);
          if (l_res != m)
            return l_res;
          else
            return find(u + u + 1, m, r, ql, qr, line);
        }
      }
    }
    else
    {
      int m = l + (r - l) / 2;
      if (qr <= m)
        return find(u + u, l, m, ql, qr, line);
      else if (ql >= m)
        return find(u + u + 1, m, r, ql, qr, line);
      else
      {
        int l_res = find(u + u, l, m, ql, qr, line);
        if (l_res != m)
          return l_res;
        else
          return find(u + u + 1, m, r, ql, qr, line);
      }
    }
  }
};

sgt_t sgt;

point_t a[N];
int     n;

int main()
{
  // see(line_t({0, 1}, {1, 0}).eval({2, 0}));
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    n = sc.next_int();
    for (int i = 0; i < n; i++)
    {
      a[i].x = sc.next_int();
      a[i].y = sc.next_int();
    }
    sgt.build(1, 0, n, a);

    std::vector<std::pair<line_t, int>> queries;

    for (int i = 0; i + 1 < n; i++)
      queries.push_back({{a[i], a[i + 1]}, i});
    std::sort(queries.begin(), queries.end(), [](auto x, auto y) {
      return x.first.x * y.first.y - x.first.y * y.first.x < 0;
    });

    std::vector<int> ans(n - 1);
    for (const auto &[l, i] : queries)
    {
      int r  = sgt.find(1, 0, n, i, n, l);
      ans[i] = r == n ? 0 : r;
    }

    std::ostream_iterator<int> out(std::cout, " ");
    std::copy(ans.begin(), ans.end(), out);
    std::cout << std::endl;
  }
  return 0;
}
