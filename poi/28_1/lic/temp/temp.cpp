#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
#include <system_error>
#include <utility>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t : public cm::segment_tree_node_base<true>
{
  using cm::segment_tree_node_base<true>::segment_tree_node_base;

  int len = 1;
  int sum = 0;
  int ass = -1;

  node_t(node_t lhs, node_t rhs) :
      len(lhs.len + rhs.len), sum(lhs.sum + rhs.sum)
  {
  }

  void assign(int v)
  {
    sum = v * len;
    ass = v;
  }

  void push_down(node_t &lhs, node_t &rhs)
  {
    if (ass != -1)
    {
      lhs.assign(ass);
      rhs.assign(ass);
      ass = -1;
    }
  }
};

int main()
{
  int n = sc.next_int();
  int q = sc.next_int();

  std::vector<int> a(n, 0), b(n, 0);
  for (int i = n - 2; i >= 0; i--)
    a[i] = sc.next_char() - '0';
  for (int i = n - 2; i >= 0; i--)
    b[i] = sc.next_char() - '0';

  cm::segment_tree<node_t> sgt(n);

  int x = 0;
  for (int i = 0; i < n; i++)
  {
    x += a[i] + b[i];
    sgt.modify(i, i + 1, &node_t::assign, x % 10);
    x = x / 10;
  }

  for (int i = 0; i < q; i++)
  {
    char opt = sc.next_char();
    if (opt == 'S')
    {
      int  id  = sc.next_int() - 1;
      auto res = sgt.query(id, id + 1);
      printf("%d\n", res.sum);
    }
    else
    {
      int id  = sc.next_int() - 1;
      int val = sc.next_int();

      int &o = opt == 'W' ? a[id] : b[id];
      int  d = val - std::exchange(o, val);

      if (d > 0)
      {
        auto cur = sgt.query(id, id + 1);
        sgt.modify(id, id + 1, &node_t::assign, (cur.sum + d) % 10);
        if (cur.sum + d >= 10)
        {
          int ll = id + 1;
          int rr = n - 1;
          while (ll < rr)
          {
            int mm = ll + (rr - ll + 1) / 2;
            if (sgt.query(id + 1, mm).sum == 9 * (mm - id - 1))
              ll = mm;
            else
              rr = mm - 1;
          }
          if (id + 1 != ll)
            sgt.modify(id + 1, ll, &node_t::assign, 0);
          cm_assert(sgt.query(ll, ll + 1).sum <= 8);
          sgt.modify(
              ll, ll + 1, &node_t::assign, sgt.query(ll, ll + 1).sum + 1);
        }
      }
      else
      {
        auto cur = sgt.query(id, id + 1);
        sgt.modify(id, id + 1, &node_t::assign, (cur.sum + d + 10) % 10);
        if (cur.sum + d < 0)
        {
          int ll = id + 1;
          int rr = n - 1;
          while (ll < rr)
          {
            int mm = ll + (rr - ll + 1) / 2;
            if (sgt.query(id + 1, mm).sum == 0)
              ll = mm;
            else
              rr = mm - 1;
          }
          if (id + 1 != ll)
            sgt.modify(id + 1, ll, &node_t::assign, 9);
          cm_assert(sgt.query(ll, ll + 1).sum >= 1);
          sgt.modify(
              ll, ll + 1, &node_t::assign, sgt.query(ll, ll + 1).sum - 1);
        }
      }
    }
  }

  return 0;
}
