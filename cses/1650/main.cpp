#pragma GCC optimize(2, 3)

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

  long long val = 0;
  sgt_node(const sgt_node &lhs, const sgt_node &rhs) : val(lhs.val ^ rhs.val) {}
  void add(int delta) { val += delta; }
};

int main()
{
  int n = sc.next_int();
  int q = sc.next_int();
  cm::segment_tree<sgt_node> sgt(n);
  for (int i = 0; i < n; i++)
    sgt.modify(i, i + 1, &sgt_node::add, sc.next_int());
  for (int i = 0; i < q; i++)
  {
    int l = sc.next_int() - 1;
    int r = sc.next_int();
    std::cout << sgt.query(l, r).val << std::endl;
  }
  return 0;
}
