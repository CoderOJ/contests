#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

const int INF = 0x3f3f3f3f;

struct node_t : public cm::segment_tree_node_base<true>
{
  using cm::segment_tree_node_base<true>::segment_tree_node_base;

  int min_h = INF;
  int max_h = -INF;
  int ans   = -1;
  int min_t = INF;
  int max_t = -INF;

  node_t(const node_t &lhs, const node_t &rhs) :
      min_h(std::min(lhs.min_h, rhs.min_h)),
      max_h(std::max(lhs.max_h, rhs.max_h)),
      ans(std::max(lhs.ans, rhs.ans))
  {
  }

  void set_minmax(int min, int max)
  {
    min_h = min;
    max_h = max;
  }

  void push_chmax(int min_v, int max_v)
  {
    ans   = std::max({ans, max_v - min_h, max_h - min_v});
    min_t = std::min(min_t, min_v);
    max_t = std::max(max_t, max_v);
  }

  void push_down(node_t &lhs, node_t &rhs)
  {
    if (min_t != INF)
    {
      lhs.push_chmax(min_t, max_t);
      rhs.push_chmax(min_t, max_t);
      min_t = INF;
      max_t = -INF;
    }
  }
};

struct anten_t
{
  int h, l, r;
};

struct query_t
{
  int l, r;
  int ans;
};

int main()
{
  int n = sc.next_int();

  std::vector<anten_t> a(n);
  for (int i = 0; i < n; i++)
  {
    a[i].h = sc.next_int();
    a[i].l = sc.next_int();
    a[i].r = sc.next_int() + 1;
  }

  int                  q = sc.next_int();
  std::vector<query_t> qs(q);
  for (int i = 0; i < q; i++)
  {
    qs[i].l = sc.next_int() - 1;
    qs[i].r = sc.next_int();
  }

  std::vector<std::vector<int>> insert(n);
  std::vector<std::vector<int>> leave(n);
  for (int i = 0; i < n; i++)
  {
    if (i + a[i].l < n)
      insert[i + a[i].l].push_back(i);
    if (i + a[i].r < n)
      leave[i + a[i].r].push_back(i);
  }

  std::vector<query_t *> qo(q);
  for (int i = 0; i < q; i++)
    qo[i] = &qs[i];
  std::sort(qo.begin(), qo.end(), [&](query_t *a, query_t *b) {
    return a->r < b->r;
  });

  auto qo_it = qo.begin();

  cm::segment_tree<node_t> sgt(0, n);
  for (int i = 0; i < n;)
  {
    for (int p : insert[i])
      sgt.modify(p, p + 1, &node_t::set_minmax, a[p].h, a[p].h);
    for (int p : leave[i])
      sgt.modify(p, p + 1, &node_t::set_minmax, INF, -INF);

    int ql = std::max(0, i - a[i].r + 1);
    int qr = std::max(0, i - a[i].l + 1);
    if (ql < qr)
      sgt.modify(ql, qr, &node_t::push_chmax, a[i].h, a[i].h);

    i++;

    for (; qo_it != qo.end() && (*qo_it)->r == i; qo_it++)
      (*qo_it)->ans = sgt.query((*qo_it)->l, (*qo_it)->r).ans;
  }

  for (int i = 0; i < q; i++)
    printf("%d\n", qs[i].ans);

  return 0;
}
