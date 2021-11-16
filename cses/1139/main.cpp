#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
#include <algorithm>
#include <functional>
#include <map>
#include <tuple>
#include <utility>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t : public cm::segment_tree_node_base<>
{
  using cm::segment_tree_node_base<>::segment_tree_node_base;
  int sum = 0;
  node_t(const node_t lhs, const node_t rhs) : sum(lhs.sum + rhs.sum)
  {
  }
  void push_add(int delta)
  {
    sum += delta;
  }
};

int main()
{
  int n = sc.next_int();
  std::vector<int> col(n);
  for (int i = 0; i < n; i++)
    col[i] = sc.next_int();
  std::vector<std::vector<int>> e(n);
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  std::vector<int> d2c(n);
  std::vector<int> dl(n), dr(n);
  int cur_dfn = 0;
  std::function<void(int, int)> dfs = [&](int u, int f) {
    dl[u] = cur_dfn++;
    d2c[dl[u]] = col[u];
    for (int v : e[u])
      if (v != f)
        dfs(v, u);
    dr[u] = cur_dfn;
  };
  dfs(0, 0);

  std::vector<std::tuple<int, int, int>> inters;
  for (int i = 0; i < n; i++)
    inters.emplace_back(dr[i], dl[i], i);
  std::sort(inters.begin(), inters.end());

  std::map<int, int> last_occur;
  cm::segment_tree<node_t> t(n);
  int cur_r = 0;
  std::vector<int> ans(n);
  for (const auto &[r, l, i] : inters)
  {
    while (cur_r < r)
    {
      t.modify(cur_r, cur_r + 1, &node_t::push_add, 1);
      auto it = last_occur.find(d2c[cur_r]);
      if (it == last_occur.end())
      {
        last_occur.emplace(d2c[cur_r], cur_r);
      }
      else
      {
        t.modify(it->second, it->second + 1, &node_t::push_add, -1);
        it->second = cur_r;
      }
      cur_r++;
    }
    ans[i] = t.query(l, r).sum;
  }

  for (int i = 0; i < n; i++)
    std::cout << ans[i] << " ";

  return 0;
}
