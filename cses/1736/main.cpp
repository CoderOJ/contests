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

  long long l, r;
  long long sum = 0;
  long long add_a = 0, add_p = 0;

  node_t(int p) : l(p), r(p + 1)
  {
  }
  node_t(const node_t &lhs, const node_t &rhs)
      : l(lhs.l), r(rhs.r), sum(lhs.sum + rhs.sum)
  {
  }

  void push_add_a(long long val)
  {
    add_a += val;
    sum += (r - l) * val;
  }
  void push_add_p(long long val)
  {
    add_p += val;
    sum += (r - l) * (l + r - 1) / 2 * val;
  }
  void push_down(node_t &lhs, node_t &rhs)
  {
    if (add_a != 0)
    {
      lhs.push_add_a(add_a);
      rhs.push_add_a(add_a);
      add_a = 0;
    }
    if (add_p != 0)
    {
      lhs.push_add_p(add_p);
      rhs.push_add_p(add_p);
      add_p = 0;
    }
  }
};

int main()
{
  int n = sc.next_int();
  int q = sc.next_int();
  cm::segment_tree<node_t> t(n);
  for (int i = 0; i < n; i++)
    t.modify(i, i + 1, &node_t::push_add_a, sc.next_long());

  for (int i = 0; i < q; i++)
  {
    int op = sc.next_int();
    if (op == 1)
    {
      int l = sc.next_int() - 1;
      int r = sc.next_int();
      t.modify(l, r, &node_t::push_add_p, 1ll);
      t.modify(l, r, &node_t::push_add_a, 1ll - l);
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
