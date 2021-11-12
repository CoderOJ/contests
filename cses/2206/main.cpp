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

  int min = 0;
  node_t(const node_t lhs, const node_t rhs) : min(std::min(lhs.min, rhs.min))
  {
  }
  void push_assign(int val)
  {
    min = val;
  }
};

int main()
{
  int n = sc.next_int();
  int q = sc.next_int();

  cm::segment_tree<node_t> ti(n), td(n);
  for (int i = 0; i < n; i++)
  {
    int a = sc.next_int();
    ti.modify(i, i + 1, &node_t::push_assign, a + i);
    td.modify(i, i + 1, &node_t::push_assign, a + n - i);
  }

  for (int i = 0; i < q; i++)
  {
    int op = sc.next_int();
    if (op == 1)
    {
      int p = sc.next_int() - 1;
      int a = sc.next_int();
      ti.modify(p, p + 1, &node_t::push_assign, a + p);
      td.modify(p, p + 1, &node_t::push_assign, a + n - p);
    }
    else
    {
      int p = sc.next_int() - 1;
      int ans_l = td.query(0, p + 1).min - (n - p);
      int ans_r = ti.query(p, n).min - p;
      std::cout << std::min(ans_l, ans_r) << std::endl;
    }
  }

  return 0;
}
