#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <cstddef>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  struct node_t
  {
    int64_t dm = 0, d = 0;

    node_t() = default;

    node_t(int64_t d, int64_t u) : dm(d), d(u) {}

    node_t(const node_t &lhs, const node_t &rhs) :
        dm(std::min(lhs.dm, lhs.d + rhs.dm)), d(lhs.d + rhs.d)
    {
    }

    bool operator<(const node_t &rhs) const
    {
      if (d > 0)
      {
        if (rhs.d > 0)
          return dm > rhs.dm;
        else
          return true;
      }
      else
      {
        if (rhs.d > 0)
          return false;
        else
          return (d - dm) > (rhs.d - rhs.dm);
      }
    }
  };

  auto read_list = [&] {
    int n = sc.next_int();

    std::vector<node_t> a;
    for (int i = 0; i < n; i++)
    {
      char    c = sc.next_char();
      int64_t x = sc.next_long();
      if (c == '(')
        a.emplace_back(0, x);
      else
        a.emplace_back(-x, -x);
    }

    return a;
  };

  auto get_reaches = [&](std::vector<node_t> a) {
    a.insert(a.begin(), node_t());

    std::vector<int> p(a.size());
    for (int i = 0; i < (int)a.size(); i++)
      p[i] = i;
    auto get = cm::y_combinate([&](auto &&self, int u) -> int {
      return u == p[u] ? u : p[u] = self(p[u]);
    });

    std::multiset<std::pair<node_t, int>> ns;
    std::vector<decltype(ns)::iterator>   its(a.size());
    for (int i = 1; i < (int)a.size(); i++)
      its[i] = ns.emplace(a[i], i);

    std::vector<node_t> res;
    while (!ns.empty())
    {
      const auto [t, tu] = *ns.begin();
      ns.erase(ns.begin());

      int tp = get(tu - 1);
      if (tp == 0)
      {
        res.push_back(t);
      }
      else
      {
        ns.erase(its[tp]);
        a[tp]   = node_t(a[tp], t);
        its[tp] = ns.emplace(a[tp], tp);
      }
      p[tu] = tp;
    }

    return res;
  };

  auto build_table = [&](const std::vector<node_t> &v, const auto &f) {
    int n = (int)v.size();

    std::vector<std::vector<node_t>> a(n);
    for (int i = n - 1; i >= 0; i--)
    {
      std::vector<node_t> &cur = a[i];

      cur = {v[i]};
      for (int j = 0; i + (1 << (j + 1)) <= n; j++)
        cur.push_back(f(a[i][j], a[i + (1 << j)][j]));
    }

    return a;
  };

  auto ar     = get_reaches(read_list());
  auto ar_sum = build_table(ar, [](node_t a, node_t b) {
    return node_t(a, b);
  });
  auto ar_max = build_table(ar, [](node_t a, node_t b) {
    return std::max(a, b);
  });

  int m = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    auto br = get_reaches(read_list());

    auto res = [&] {
      node_t res;

      int ap = 0;
      for (const auto &bc: br)
      {
        for (int i = 20; i >= 0; i--)
          if (ap + (1 << i) <= (int)ar.size())
            if (ar_max[ap][i] < bc)
            {
              res = node_t(res, ar_sum[ap][i]);
              ap += (1 << i);
            }
        res = node_t(res, bc);
      }
      for (int i = 20; i >= 0; i--)
        if (ap + (1 << i) <= (int)ar.size())
        {
          res = node_t(res, ar_sum[ap][i]);
          ap += (1 << i);
        }

      return res;
    }();

    if (res.dm >= 0 && res.d == 0)
      puts("1");
    else
      puts("0");
  }

  return 0;
}
