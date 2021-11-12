#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t : public cm::segment_tree_node_base
{
  using cm::segment_tree_node_base::segment_tree_node_base;

  long long sum, max, max_prefix, max_suffix;
  node_t(const node_t &lhs, const node_t &rhs)
      : sum(lhs.sum + rhs.sum),
        max(std::max({lhs.max, rhs.max, lhs.max_suffix + rhs.max_prefix})),
        max_prefix(std::max({lhs.max_prefix, lhs.sum + rhs.max_prefix})),
        max_suffix(std::max({lhs.max_suffix + rhs.sum, rhs.max_suffix}))
  {
  }

  void push_assign(int val)
  {
    sum = val;
    max = std::max(0, val);
    max_prefix = max;
    max_suffix = max;
  }
};

int main()
{
  int n = sc.next_int();
  int q = sc.next_int();
  cm::segment_tree<node_t> t(n);
  for (int i = 0; i < n; i++)
    t.modify(i, i + 1, &node_t::push_assign, sc.next_int());

  for (int i = 0; i < q; i++)
  {
    int p = sc.next_int() - 1;
    int x = sc.next_int();
    t.modify(p, p + 1, &node_t::push_assign, x);
    std::cout << t.query(0, n).max << std::endl;
  }

  return 0;
}
