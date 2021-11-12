#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t : public cm::segment_tree_node_base<true>
{
  using cm::segment_tree_node_base<true>::segment_tree_node_base;

  long long len = 1;
  long long sum = 0;
  long long add = 0;
  long long assign = -1;

  node_t(const node_t &lhs, const node_t &rhs)
      : len(lhs.len + rhs.len), sum(lhs.sum + rhs.sum)
  {
  }

  void push_add(long long val)
  {
    add += val;
    sum += len * val;
  }
  void push_assign(long long val)
  {
    add = 0;
    assign = val;
    sum = len * val;
  }
  void push_down(node_t &lhs, node_t &rhs)
  {
    if (assign != -1)
    {
      lhs.push_assign(assign);
      rhs.push_assign(assign);
      assign = -1;
    }
    if (add != 0)
    {
      lhs.push_add(add);
      rhs.push_add(add);
      add = 0;
    }
  }
};

int main()
{
  int n = sc.next_int();
  int q = sc.next_int();
  cm::segment_tree<node_t> t(n);
  for (int i = 0; i < n; i++)
    t.modify(i, i + 1, &node_t::push_add, sc.next_long());

  for (int i = 0; i < q; i++)
  {
    int opt = sc.next_int();
    if (opt == 1)
    {
      int l = sc.next_int() - 1;
      int r = sc.next_int();
      long long x = sc.next_long();
      t.modify(l, r, &node_t::push_add, x);
    }
    else if (opt == 2)
    {
      int l = sc.next_int() - 1;
      int r = sc.next_int();
      long long x = sc.next_long();
      t.modify(l, r, &node_t::push_assign, x);
    }
    else
    {
      int l = sc.next_int() - 1;
      int r = sc.next_int();
      std::cout << t.query(l, r).sum << std::endl;
    }
  }

  return 0;
}
