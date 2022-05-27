#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
#include <algorithm>
#include <stack>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 2000005, 1005)

int l[N], r[N], n;

struct node_t : public cm::segment_tree_node_base<false>
{
  using cm::segment_tree_node_base<false>::segment_tree_node_base;

  std::pair<int, int> min{0x3f3f3f3f, -1};

  node_t() = default;
  node_t(int a, int b) : min{a, b} {}
  node_t(node_t lhs, node_t rhs) : min(std::min(lhs.min, rhs.min)) {}

  void assign(node_t rhs)
  {
    *this = rhs;
  }
};

cm::segment_tree<node_t> slr, srl;

int  col[N];
void dfs(int u, int c)
{
  see(u, c);
  col[u] = c;
  slr.modify(l[u], l[u] + 1, &node_t::assign, node_t());
  srl.modify(r[u], r[u] + 1, &node_t::assign, node_t());
  while (true)
  {
    auto t = slr.query(l[u], r[u]);
    if (-t.min.first <= r[u])
      break;
    dfs(t.min.second, 1 - c);
  }
  while (true)
  {
    auto t = srl.query(l[u], r[u]);
    if (t.min.first >= l[u])
      break;
    dfs(t.min.second, 1 - c);
  }
}

struct node_or_t : public cm::segment_tree_node_base<false>
{
  using cm::segment_tree_node_base<false>::segment_tree_node_base;

  int val_or = 0;
  node_or_t(int v, int) : val_or(v) {}
  node_or_t(node_or_t lhs, node_or_t rhs) : val_or(lhs.val_or | rhs.val_or) {}

  void assign(node_or_t rhs)
  {
    *this = rhs;
  }
};

int main()
{
  n   = sc.next_int();
  slr = cm::segment_tree<node_t>(n * 2);
  srl = cm::segment_tree<node_t>(n * 2);
  for (int i = 0; i < n; i++)
  {
    l[i] = sc.next_int() - 1;
    r[i] = sc.next_int() - 1;
    slr.modify(l[i], l[i] + 1, &node_t::assign, node_t(-r[i], i));
    srl.modify(r[i], r[i] + 1, &node_t::assign, node_t(l[i], i));
  }

  int cnt = 0;
  std::fill(col, col + n, -1);
  for (int i = 0; i < n; i++)
    if (col[i] == -1)
    {
      see("starts", i);
      dfs(i, 0);
      cnt += 1;
    }

  cm::segment_tree<node_or_t> sgt(n * 2);
  std::vector<int>            ids(n);
  for (int i = 0; i < n; i++)
    ids[i] = i;
  std::sort(ids.begin(), ids.end(), [](int x, int y) { return l[x] < l[y]; });
  for (int i : ids)
  {
    auto t = sgt.query(l[i], r[i]);
    see(t.val_or);
    if (t.val_or & (1 << col[i]))
    {
      puts("0");
      return 0;
    }
    sgt.modify(r[i], r[i] + 1, &node_or_t::assign, node_or_t(1 << col[i], 0));
  }

  int ans = 1;
  for (int i = 0; i < cnt; i++)
    ans = (ans + ans) % 1000000007;
  std::cout << ans << std::endl;

  return 0;
}
