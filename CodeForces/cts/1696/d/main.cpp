#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/scanner.hpp"
#include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t : public cm::segment_tree_node_base<false>
{
  using cm::segment_tree_node_base<false>::segment_tree_node_base;

  int min = 0;
  int max = 0;

  node_t() = default;
  node_t(const node_t &lhs, const node_t &rhs) :
      min(std::min(lhs.min, rhs.min)), max(std::max(lhs.max, rhs.max))
  {
  }

  void set_val(int val)
  {
    min = val;
    max = val;
  }
};

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();

    std::vector<int> a2p(n);
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
      a[i]      = sc.next_int() - 1;
      a2p[a[i]] = i;
    }

    cm::segment_tree<node_t> sgt(n);
    for (int i = 0; i < n; i++)
      sgt.modify(i, i + 1, &node_t::set_val, a[i]);

    int ans = cm::y_combinate([&](auto &&self, int l, int r) -> int {
      if (l == r)
      {
        return 0;
      }
      else
      {
        auto p   = sgt.query(l, r + 1);
        int  min = p.min, max = p.max;
        int  min_p = a2p[min], max_p = a2p[max];
        if (min_p != l && min_p != r)
          return self(l, min_p) + self(min_p, r);
        else if (max_p != l && max_p != r)
          return self(l, max_p) + self(max_p, r);
        else
          return 1;
      }
    })(0, n - 1);

    std::cout << ans << std::endl;
  }
  return 0;
}
