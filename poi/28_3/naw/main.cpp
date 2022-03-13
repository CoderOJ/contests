#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1'000'005;

char ans[N];
int  p[N];
int  n;

struct node_t : public cm::segment_tree_node_base<true>
{
  using cm::segment_tree_node_base<true>::segment_tree_node_base;

  int max = 0;
  int add = 0;

  node_t(const node_t &lhs, const node_t &rhs) : max(std::max(lhs.max, rhs.max))
  {
  }

  void push_add(int val)
  {
    max += val;
    add += val;
  }

  void push_down(node_t &lhs, node_t &rhs)
  {
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
  n = sc.next_int();
  for (int i = 0; i < n; i++)
    p[i] = sc.next_int() - 1;

  cm::segment_tree<node_t> sgt(n);

  for (int i = 0; i < n; i++)
    sgt.modify(i, i + 1, &node_t::push_add, i - n);

  for (int i = 0; i < n; i++)
  {
    int j   = p[i];
    int max = sgt.query(0, j + 1).max;
    if (max + 2 > 0)
      ans[i] = ')';
    else
    {
      ans[i] = '(';
      sgt.modify(0, j + 1, &node_t::push_add, 2);
    }
  }

  int cur = 0;
  for (int i = 0; i < n; i++)
  {
    cur += ans[i] == '(' ? 1 : -1;
    if (cur < 0)
    {
      puts("NIE");
      return 0;
    }
  }

  puts(ans);

  return 0;
}
