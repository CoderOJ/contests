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

  long long val = 0, add = 0;
  sgt_node(const sgt_node &lhs, const sgt_node &rhs) : val(lhs.val + rhs.val) {}
  void push_add(long long delta)
  {
    val += delta;
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
  cm::segment_tree<sgt_node> sgt(n);
  for (int i = 0; i < n; i++)
    sgt.modify(i, i + 1, &sgt_node::push_add, sc.next_long());
  for (int i = 0; i < q; i++)
  {
    int op = sc.next_int();
    if (op == 1)
    {
      int l = sc.next_int() - 1;
      int r = sc.next_int();
      sgt.modify(l, r, &sgt_node::push_add, sc.next_long());
    }
    else
    {
      int p = sc.next_int() - 1;
      std::cout << sgt.query(p, p + 1).val << std::endl;
    }
  }
  return 0;
}
