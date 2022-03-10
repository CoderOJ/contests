#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
#include <algorithm>
#include <numeric>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 500'005, 55)

int n, m, q;
int a[N], b[N];

struct node_t : public cm::segment_tree_node_base<false>
{
  using cm::segment_tree_node_base<false>::segment_tree_node_base;

  int64_t sum        = 0;
  int64_t min_suffix = 0;

  node_t(const node_t lhs, const node_t rhs) :
      sum(lhs.sum + rhs.sum),
      min_suffix(std::min(lhs.min_suffix + rhs.sum, rhs.min_suffix))
  {
  }

  void add(int val)
  {
    sum += val;
    min_suffix = std::min<int64_t>(sum, 0);
  }
};

cm::segment_tree<node_t> sgt(N);

int a_cnt[N];
int b_sorted[N];

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  for (int j = 0; j < m; j++)
    b[j] = sc.next_int();

  {
    for (int i = 0; i < n; i++)
      a_cnt[a[i]] += 1;
    int cur = n;
    for (int i = 0; i < N; i++)
    {
      cur -= a_cnt[i];
      sgt.modify(i, i + 1, &node_t::add, -cur);
    }
  }

  {
    std::copy(b, b + m, b_sorted);
    std::sort(b_sorted, b_sorted + m, std::greater<int>());
    for (int i = 0; i < N; i++)
      sgt.modify(i, i + 1, &node_t::add, b_sorted[i]);
  }

  q = sc.next_int();

  for (int i = 0; i < q; i++)
  {
    int opt = sc.next_int();
    int x   = sc.next_int() - 1;
    if (opt == 1)
    {
      sgt.modify(a[x], a[x] + 1, &node_t::add, -1);
      a[x] += 1;
    }
    else if (opt == 2)
    {
      a[x] -= 1;
      sgt.modify(a[x], a[x] + 1, &node_t::add, 1);
    }
    else if (opt == 3)
    {
      auto it =
          std::lower_bound(b_sorted, b_sorted + m, b[x], std::greater<int>());
      int it_id = static_cast<int>(it - b_sorted);
      b[x] += 1;
      *it += 1;
      sgt.modify(it_id, it_id + 1, &node_t::add, 1);
    }
    else
    {
      auto it =
          std::upper_bound(b_sorted, b_sorted + m, b[x], std::greater<int>()) -
          1;
      int it_id = static_cast<int>(it - b_sorted);
      b[x] -= 1;
      *it -= 1;
      sgt.modify(it_id, it_id + 1, &node_t::add, -1);
    }

    auto min_suffix = sgt.query(0, N).min_suffix;
    std::cout << (min_suffix < 0 ? 0 : 1) << '\n';
  }

  return 0;
}
