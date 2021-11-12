#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
#include <algorithm>
#include <map>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t : public cm::segment_tree_node_base
{
  using cm::segment_tree_node_base::segment_tree_node_base;

  int sum = 0;
  node_t(const node_t lhs, const node_t rhs) : sum(lhs.sum + rhs.sum)
  {
  }
  void push_add(int val)
  {
    sum += val;
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
  for (int &x : a)
    x = sc.next_int();
  std::vector<query_t> qs;
  for (int i = 0; i < q; i++)
  {
    int l = sc.next_int() - 1;
    int r = sc.next_int();
    qs.emplace_back(l, r, i);
  }

  std::vector<int> ans(q);
  cm::segment_tree<node_t> pos2ans(n);
  std::map<int, int> last_occur;
  int cur_r = 0;
  std::sort(qs.begin(), qs.end(),
            [](query_t lhs, query_t rhs) { return lhs.r < rhs.r; });
  for (const auto &[l, r, i] : qs)
  {
    while (cur_r < r)
    {
      pos2ans.modify(cur_r, cur_r + 1, &node_t::push_add, 1);
      auto it = last_occur.find(a[cur_r]);
      if (it != last_occur.end())
      {
        pos2ans.modify(it->second, it->second + 1, &node_t::push_add, -1);
        it->second = cur_r;
      }
      else
      {
        last_occur.emplace(a[cur_r], cur_r);
      }
      cur_r++;
    }
    ans[i] = pos2ans.query(l, r).sum;
  }

  for (int x : ans)
    std::cout << x << std::endl;

  return 0;
}
