#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
#include <algorithm>
#include <numeric>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t : public cm::segment_tree_node_base<true>
{
  using cm::segment_tree_node_base<true>::segment_tree_node_base;

  int max    = 0;
  int max_id = 0;
  int add    = 0;

  node_t(const node_t &lhs, const node_t &rhs) :
      max(std::max(lhs.max, rhs.max)),
      max_id(lhs.max == max ? lhs.max_id : rhs.max_id)
  {
  }

  node_t(int id) : max_id(id) {}

  void push_add(int det)
  {
    max += det;
    add += det;
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
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();
    int k = sc.next_int();

    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int();

    cm::segment_tree<node_t> sgt(0, n);
    for (int i = 0; i < n; i++)
      sgt.modify(i, i + 1, &node_t::push_add, a[i] - (n - i - 1));

    std::vector<bool> ban_pos(n, false);
    for (int i = 0; i < k; i++)
    {
      auto max = sgt.query(0, n);
      // see(max.max, max.max_id);
      if (max.max > 0)
      {
        ban_pos[max.max_id] = true;
        sgt.modify(0, n, &node_t::push_add, 1);
        sgt.modify(max.max_id, max.max_id + 1, &node_t::push_add, -0x3f3f3f3f);
      }
      else
      {
        break;
      }
    }

    int64_t ans = 0, acc = 0;
    for (int i = 0; i < n; i++)
    {
      if (ban_pos[i])
        acc += 1;
      else
        ans += a[i] + acc;
    }
    std::cout << ans << std::endl;
  }
  return 0;
}
