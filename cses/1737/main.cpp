#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstdlib>
#include <iterator>
#include <memory>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct sgt_node_t
{
  std::shared_ptr<sgt_node_t> ls, rs;
  int l, r;
  long long sum;
  sgt_node_t(int l, int r) : l(l), r(r)
  {
  }
};

std::shared_ptr<sgt_node_t> build(const int *a, int l, int r)
{
  cm_assert(l != r);
  if (l + 1 == r)
  {
    auto res = std::make_shared<sgt_node_t>(l, r);
    res->sum = a[l];
    return res;
  }
  else
  {
    int mid = (l + r) / 2;
    auto res = std::make_shared<sgt_node_t>(l, r);
    res->ls = build(a, l, mid);
    res->rs = build(a, mid, r);
    res->sum = res->ls->sum + res->rs->sum;
    return res;
  }
}

std::shared_ptr<sgt_node_t> update(const std::shared_ptr<sgt_node_t> &u, int p,
                                   int val)
{
  if (u->l + 1 == u->r)
  {
    auto res = std::make_shared<sgt_node_t>(u->l, u->r);
    res->sum = val;
    return res;
  }
  else
  {
    int mid = (u->l + u->r) / 2;
    auto res = std::make_shared<sgt_node_t>(u->l, u->r);
    if (p < mid)
    {
      res->ls = update(u->ls, p, val);
      res->rs = u->rs;
    }
    else
    {
      res->ls = u->ls;
      res->rs = update(u->rs, p, val);
    }
    res->sum = res->ls->sum + res->rs->sum;
    return res;
  }
}

long long query(const std::shared_ptr<sgt_node_t> &u, int l, int r)
{
  if (l <= u->l && u->r <= r)
  {
    return u->sum;
  }
  else
  {
    int mid = (u->l + u->r) / 2;
    if (r <= mid)
      return query(u->ls, l, r);
    else if (l >= mid)
      return query(u->rs, l, r);
    else
      return query(u->ls, l, r) + query(u->rs, l, r);
  }
}

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  std::vector<std::shared_ptr<sgt_node_t>> his;
  his.emplace_back(build(a.data(), 0, n));

  for (int i = 0; i < m; i++)
  {
    int op = sc.next_int();
    if (op == 1)
    {
      int k = sc.next_int() - 1;
      int i = sc.next_int() - 1;
      int v = sc.next_int();
      his[k] = update(his[k], i, v);
    }
    else if (op == 2)
    {
      int k = sc.next_int() - 1;
      int l = sc.next_int() - 1;
      int r = sc.next_int();
      std::cout << query(his[k], l, r) << std::endl;
    }
    else
    {
      int k = sc.next_int() - 1;
      his.emplace_back(his[k]);
    }
  }

  return 0;
}
