#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t : public cm::segment_tree_node_base<true>
{
  using cm::segment_tree_node_base<true>::segment_tree_node_base;

  int max     = 0;
  int max_cnt = 1;
  int add     = 0;

  node_t() = default;
  node_t(const node_t &lhs, const node_t &rhs) :
      max(std::max(lhs.max, rhs.max)),
      max_cnt((lhs.max == max ? lhs.max_cnt : 0) +
              (rhs.max == max ? rhs.max_cnt : 0))
  {
  }

  void push_add(int det)
  {
    add += det;
    max += det;
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
    printf("Case #%d: ", i + 1);

    int n = sc.next_int();
    int c = sc.next_int();

    std::vector<std::pair<int, int>> c_inter(c);
    for (int i = 0; i < c; i++)
    {
      c_inter[i].first  = sc.next_int();
      c_inter[i].second = sc.next_int() + 1;
    }

    std::vector<int> a(n + n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int() - 1;
    std::copy(a.begin(), a.begin() + n, a.begin() + n);

    int64_t ans = 0;
    for (int l = 0; l < n; l++)
      for (int r = l + 2; r <= l + n; r++)
      {

      }

    std::cout << ans << std::endl;
  }
  return 0;
}
