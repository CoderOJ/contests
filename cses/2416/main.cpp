#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
#include <algorithm>
#include <limits>
#include <utility>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t : public cm::segment_tree_node_base
{
  using cm::segment_tree_node_base::segment_tree_node_base;
  static constexpr bool have_push_down = true;

  long long len = 1, sum = 0;
  int assign = -1;
  node_t(const node_t &lhs, const node_t &rhs)
      : len(lhs.len + rhs.len), sum(lhs.sum + rhs.sum)
  {
  }

  void push_assign(int val)
  {
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
  }
};

struct query_t
{
  int l, r, id;
  query_t(int l, int r, int id) : l(l), r(r), id(id)
  {
  }
};

int main()
{
  int n = sc.next_int();
  int q = sc.next_int();
  std::vector<int> a(n);
  std::vector<long long> pa(n + 1);
  for (int i = 0; i < n; i++)
  {
    a[i] = sc.next_int();
    pa[i + 1] = pa[i] + a[i];
  }

  std::vector<query_t> qs;
  for (int i = 0; i < q; i++)
  {
    int l = sc.next_int() - 1;
    int r = sc.next_int();
    qs.emplace_back(l, r, i);
  }

  std::vector<long long> ans(q);
  cm::segment_tree<node_t> t(n);
  std::vector<std::pair<int, int>> stack{{n, std::numeric_limits<int>::max()}};
  int cur_l = n;
  std::sort(qs.begin(), qs.end(),
            [](query_t lhs, query_t rhs) { return lhs.l > rhs.l; });
  for (const auto &[l, r, i] : qs)
  {
    while (cur_l > l)
    {
      cur_l--;
      while (stack.back().second <= a[cur_l])
        stack.pop_back();
      int cur_r = stack.back().first;
      stack.emplace_back(cur_l, a[cur_l]);
      t.modify(cur_l, cur_r, &node_t::push_assign, a[cur_l]);
    }
    ans[i] = t.query(l, r).sum - (pa[r] - pa[l]);
  }

  for (int i = 0; i < q; i++)
    std::cout << ans[i] << std::endl;

  return 0;
}
