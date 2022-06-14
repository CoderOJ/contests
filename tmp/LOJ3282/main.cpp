#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <limits>
#include <tuple>
#include <utility>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

using range_t  = std::pair<int, int>;
using square_t = std::tuple<range_t, range_t>;

bool range_in(range_t a, range_t b)
{
  return a.first <= b.first && b.second <= a.second;
}

bool range_intersect(range_t a, range_t b)
{
  return !(a.second < b.first) && !(b.second < a.first);
}

range_t range_join(range_t a, range_t b)
{
  return {std::min(a.first, b.first), std::max(a.second, b.second)};
}

struct kdt_t
{
  struct node_t
  {
    square_t bound;

    bool is_in(square_t p)
    {
      return range_in(std::get<0>(p), std::get<0>(bound)) &&
             range_in(std::get<1>(p), std::get<1>(bound));
    }

    bool is_intersect(square_t p)
    {
      return range_intersect(std::get<0>(p), std::get<0>(bound)) &&
             range_intersect(std::get<1>(p), std::get<1>(bound));
    }

    int64_t min     = std::numeric_limits<int64_t>::max();
    int64_t min_tag = std::numeric_limits<int64_t>::max();
    int     id      = -1;

    node_t() = default;
    node_t(int x, int y, int64_t min, int id) :
        bound{{x, x}, {y, y}}, min{min}, id{id}
    {
    }

    void push_check_min(int64_t val)
    {
      if (id != -1)
      {
        check_min(min, val);
        check_min(min_tag, val);
      }
    }

    void push_up(const node_t &lhs, const node_t &rhs)
    {
      min = std::min(lhs.min, rhs.min);
      id  = lhs.min == min ? lhs.id : rhs.id;
    }

    void push_down(node_t &lhs, node_t &rhs)
    {
      if (min_tag != std::numeric_limits<int64_t>::max())
      {
        lhs.push_check_min(min_tag);
        rhs.push_check_min(min_tag);
        min_tag = std::numeric_limits<int64_t>::max();
      }
    }
  };

  size_t              n;
  std::vector<node_t> p;
  std::vector<int>    id2p;

  template <class Iter>
  kdt_t(Iter l, Iter r) : n(std::distance(l, r)), p(n * 4), id2p(n)
  {
    build<0>(1, l, r);
  }

  template <int axis, class Iter>
  void build(int u, Iter l, Iter r)
  {
    if (std::distance(l, r) == 1)
    {
      p[u]        = *l;
      id2p[l->id] = u;
    }
    else
    {
      std::sort(l, r, [](node_t a, node_t b) {
        return std::get<axis>(a.bound).first < std::get<axis>(b.bound).first;
      });

      auto m = l + std::distance(l, r) / 2;
      build<(axis + 1) % 2>(u + u, l, m);
      build<(axis + 1) % 2>(u + u + 1, m, r);
      p[u].push_up(p[u + u], p[u + u + 1]);
      p[u].bound = {
          range_join(std::get<0>(p[u + u].bound),
                     std::get<0>(p[u + u + 1].bound)),
          range_join(std::get<1>(p[u + u].bound),
                     std::get<1>(p[u + u + 1].bound)),
      };
    }
  }

  void modify(int u, const square_t &r, int64_t v)
  {
    if (p[u].is_in(r))
    {
      p[u].push_check_min(v);
    }
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      if (p[u + u].is_intersect(r))
        modify(u + u, r, v);
      if (p[u + u + 1].is_intersect(r))
        modify(u + u + 1, r, v);
      p[u].push_up(p[u + u], p[u + u + 1]);
    }
  }

  void push_chain(int u)
  {
    if (u != 1)
      push_chain(u / 2);
    p[u].push_down(p[u + u], p[u + u + 1]);
  }

  void ban(int id)
  {
    int u = id2p[id];
    if (u != 1)
      push_chain(u / 2);

    p[u].min = std::numeric_limits<int64_t>::max();
    p[u].id  = -1;
    while (u != 1)
    {
      u /= 2;
      p[u].push_up(p[u + u], p[u + u + 1]);
    }
  }
};

int main()
{
  int n = sc.next_int() + 1;
  int m = sc.next_int();

  struct line_t
  {
    int t, l, r, c;
  };

  std::vector<line_t> a(m);
  for (int i = 0; i < m; i++)
  {
    a[i].t = sc.next_int();
    a[i].l = sc.next_int();
    a[i].r = sc.next_int() + 1;
    a[i].c = sc.next_int();
  }

  std::vector<kdt_t::node_t> pn;
  pn.reserve(m);
  for (int i = 0; i < m; i++)
    pn.emplace_back(a[i].t + a[i].l,
                    a[i].t - a[i].l,
                    a[i].l == 1 ? 0 : (std::numeric_limits<int64_t>::max() - 1),
                    i);

  kdt_t kdt(pn.begin(), pn.end());

  int64_t ans = std::numeric_limits<int64_t>::max();
  for (int i = 0; i < m; i++)
  {
    int     u  = kdt.p[1].id;
    int64_t ud = kdt.p[1].min;
    see(u, ud);

    if (ud == std::numeric_limits<int64_t>::max() - 1)
      break;

    if (a[u].r == n)
      check_min(ans, ud + a[u].c);

    kdt.ban(u);
    kdt.modify(1,
               {{std::numeric_limits<int>::min(), a[u].t + a[u].r},
                {a[u].t - a[u].r, std::numeric_limits<int>::max()}},
               ud + a[u].c);
  }

  if (ans == std::numeric_limits<int64_t>::max())
    puts("-1");
  else
    std::cout << ans << std::endl;

  return 0;
}
