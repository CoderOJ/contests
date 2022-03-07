#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstdint>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 500'005;

int64_t a[3][N];
int     n, q;

struct inter_t
{
  int     l, r;
  int64_t w;
};

std::vector<inter_t> qs;

struct node_t : public cm::segment_tree_node_base<false>
{
  using cm::segment_tree_node_base<false>::segment_tree_node_base;

  int64_t max = -0x3f3f3f3f3f3f3f3f;

  node_t(node_t lhs, node_t rhs) : max(std::max(lhs.max, rhs.max)) {}

  void check_max(int64_t val)
  {
    cm::check_max(max, val);
  }
};

int64_t solve(int l, int r, const std::vector<inter_t> &_qs)
{
  see(l, r);

  std::vector<inter_t> qs;
  int64_t              all_min = 0x3f3f3f3f3f3f3f3f;
  for (const auto q : _qs)
  {
    int cl = std::max(q.l, l);
    int cr = std::min(q.r, r);
    if (cl < cr)
    {
      if (cl == l && cr == r)
        check_min(all_min, q.w);
      else
        qs.push_back({cl, cr, q.w});
    }
  }
  if (all_min < 0x3f3f3f3f3f3f3f3f)
    qs.push_back({l, r, all_min});
  std::sort(qs.begin(), qs.end(), [](auto x, auto y) { return x.r < y.r; });

  int mid = l + (r - l) / 2;

  cm::segment_tree<node_t> sgt(l, r + 1);

  auto it = qs.begin();

  int64_t prev_sum = a[0][l];
  for (int i = l; i < mid; i++)
    prev_sum += a[1][i];
  int64_t suff_sum = a[1][mid];
  int64_t suff_max = -0x3f3f3f3f3f3f3f3f;
  int64_t ans      = -0x3f3f3f3f3f3f3f3f;
  for (int i = mid; i < r; i++)
    suff_sum += a[2][i];

  for (int i = l; i < r; i++)
  {
    check_max(suff_max, suff_sum);
    if (i <= mid)
      sgt.modify(i, i + 1, &node_t::check_max, prev_sum);
    while (it != qs.end() && it->r <= i + 1)
    {
      if (it->r == i + 1)
      {
        int64_t cur = sgt.query(it->l, it->r).max;
        see(it->l, it->r, it->w);
        see(prev_sum, suff_sum);
        see(cur, suff_max);
        if (i >= mid)
          check_max(ans, cur + suff_max - it->w);
        if (i + 2 <= r)
          sgt.modify(i + 1, i + 2, &node_t::check_max, cur - it->w);
      }
      it++;
    }
    if (i < mid)
    {
      prev_sum -= a[1][i];
      prev_sum += a[0][i + 1];
    }
    else
    {
      suff_sum -= a[2][i];
      suff_sum += a[1][i + 1];
    }
  }
  if (l != mid)
  {
    int64_t l_ans = 0;
    for (int i = mid; i < r; i++)
      l_ans += a[2][i];
    l_ans += solve(l, mid, qs);
    check_max(ans, l_ans);
  }
  if (mid != r - 1)
  {
    int64_t r_ans = 0;
    for (int i = l; i <= mid; i++)
      r_ans += a[0][i];
    r_ans += solve(mid + 1, r, qs);
    check_max(ans, r_ans);
  }
  return ans;
}

int main()
{
  n = sc.next_int();
  q = sc.next_int();
  for (auto &c : a)
    for (int i = 0; i < n; i++)
      c[i] = sc.next_int();
  for (int i = 0; i < q; i++)
  {
    int     l = sc.next_int() - 1;
    int     r = sc.next_int();
    int64_t w = sc.next_int();
    qs.push_back({l, r, w});
  }
  std::cout << solve(0, n, qs) << std::endl;
  return 0;
}
