#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <iterator>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

struct dsu_t
{
  struct node_t
  {
    node_t *p;

    int min_u;
    int max_u;

    node_t *get_p()
    {
      return p == this ? this : p = p->get_p();
    }
  };

  std::vector<node_t> p;

  dsu_t(int n) : p(n)
  {
    for (int u = 0; u < n; u++)
    {
      p[u].p     = &p[u];
      p[u].min_u = u;
      p[u].max_u = u;
    }
  }

  void join(node_t *pu, node_t *pv)
  {
    pu        = pu->get_p();
    pv        = pv->get_p();
    pu->max_u = std::max(pu->max_u, pv->max_u);
    pu->min_u = std::min(pu->min_u, pv->min_u);
    pv->p     = pu;
  }
};

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();

    std::vector e(n, std::vector<bool>(n + 1));
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j <= n; j++)
        e[i][j] = sc.next_char() == '1';

    dsu_t dsu(n);

    for (int len = 1; len <= n; len++)
      for (int i = 0; i + len <= n; i++)
      {
        int l = i, r = i + len;
        if (e[l][r] && dsu.p[l].get_p() != dsu.p[r - 1].get_p())
        {
          auto us = [&] {
            std::vector<dsu_t::node_t *> a;
            for (int p = l; p < r; p++)
            {
              auto cp = dsu.p[p].get_p();
              if (a.empty() || a.back() != cp)
                a.push_back(cp);
            }
            return a;
          }();
          // see(us);

          cm_assert(us.size() != 3);

          auto order = [&] {
            std::vector<dsu_t::node_t *> a;

            auto itl = us.begin(), itr = std::prev(us.end());
            bool pos = false;

            while (itl != itr)
            {
              if (pos)
              {
                a.push_back(*itr);
                itr--;
              }
              else
              {
                a.push_back(*itl);
                itl++;
              }
              pos = !pos;
            }

            a.insert(a.begin(), *itl);

            return a;
          }();
          // see(order);

          for (size_t i = 0; i + 1 < order.size(); i++)
          {
            auto u = order[i], v = order[i + 1];
            if (u->min_u > v->min_u)
              std::swap(u, v);

            int ui = std::max(l, u->min_u);
            int vi = std::min(r - 1, v->max_u);

            std::cout << ui + 1 << " " << vi + 1 << std::endl;
            dsu.join(u, v);
          }
        }
      }
  }
  return 0;
}
