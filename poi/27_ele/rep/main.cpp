#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
#include <algorithm>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t : public cm::segment_tree_node_base<false>
{
  using cm::segment_tree_node_base<false>::segment_tree_node_base;

  int min    = 0;
  int min_id = 0;
  int cnt    = 0;

  node_t(int min, int min_id, int cnt) : min(min), min_id(min_id), cnt(cnt) {}
  node_t(const node_t &lhs, const node_t &rhs) :
      min(std::min(lhs.min, rhs.min)),
      min_id(min == lhs.min ? lhs.min_id : rhs.min_id),
      cnt(lhs.cnt + rhs.cnt)
  {
  }

  void assign(node_t rhs)
  {
    *this = rhs;
  }
};

int main()
{
  int n = sc.next_int();

  cm::segment_tree<node_t> sgt(n);
  for (int i = 0; i < n; i++)
  {
    int x = sc.next_int();
    sgt.modify(i, i + 1, &node_t::assign, node_t(x, i, 0));
  }

  int m = sc.next_int();

  std::vector<std::tuple<int, int, int, int>> qs(m);
  for (int i = 0; i < m; i++)
  {
    int l = sc.next_int() - 1;
    int r = sc.next_int();
    int k = sc.next_int();
    qs[i] = {r - l, l, r, k};
  }

  std::sort(qs.begin(), qs.end());

  int64_t          tot = 0;
  std::vector<int> ids;
  for (const auto &[_, l, r, k] : qs)
  {
    while (true)
    {
      auto v = sgt.query(l, r);
      if (v.cnt >= k)
        break;
      int id = v.min_id;
      ids.push_back(id);
      tot += v.min;
      sgt.modify(id, id + 1, &node_t::assign, node_t(0x3f3f3f3f, id, 1));
    }
  }

  std::sort(ids.begin(), ids.end());

  std::cout << tot << std::endl;
  std::cout << ids.size() << std::endl;
  for (int x : ids)
    std::cout << x + 1 << " ";
  std::cout << std::endl;

  return 0;
}
