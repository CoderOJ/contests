#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree.hpp"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct sgt_node : public cm::segment_tree_node_base
{
  using cm::segment_tree_node_base::segment_tree_node_base;
  static constexpr bool have_push_down = true;

  long long max = 0, add = 0;
  sgt_node(const sgt_node &lhs, const sgt_node &rhs)
      : max(std::max(lhs.max, rhs.max))
  {
  }
  void push_add(long long delta)
  {
    max += delta;
    add += delta;
  }
  void push_down(sgt_node &l, sgt_node &r)
  {
    l.push_add(add);
    r.push_add(add);
    add = 0;
  }
};

int main()
{
  int n = sc.next_int();
  int q = sc.next_int();
  std::vector<long long> a(n);

  cm::segment_tree<sgt_node> sgt(n);
  for (int i = 0; i < n; i++)
    sgt.modify(i, n, &sgt_node::push_add, a[i] = sc.next_long());

  for (int i = 0; i < q; i++)
  {
    int op = sc.next_int();
    if (op == 1)
    {
      int p = sc.next_int() - 1;
      long long val = sc.next_int();
      sgt.modify(p, n, &sgt_node::push_add, val - a[p]);
      a[p] = val;
    }
    else
    {
      int l = sc.next_int() - 1;
      int r = sc.next_int();
      long long pre = l ? sgt.query(l - 1, l).max : 0;
      std::cout << std::max(0ll, sgt.query(l, r).max - pre) << std::endl;
    }
  }
  return 0;
}
