#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
#include <cinttypes>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t : public cm::segment_tree_node_base<false>
{
  using cm::segment_tree_node_base<false>::segment_tree_node_base;

  int s, t;
  int64_t c;
  node_t(int l, int r) : s(l), t(r), c(-1) {}
  node_t(const node_t &lhs, const node_t &rhs)
  {
    if (lhs.c == -1)
    {
      if (rhs.c == -1)
      {
        if (lhs.t < rhs.s)
        {
          s = lhs.t;
          t = rhs.s;
          c = 0;
        }
        else if (lhs.s > rhs.t)
        {
          s = lhs.s;
          t = rhs.t;
          c = lhs.s - rhs.t;
        }
        else
        {
          s = std::max(lhs.s, rhs.s);
          t = std::min(lhs.t, rhs.t);
          c = -1;
        }
      }
      else
      {
        s = std::max(lhs.s, std::min(lhs.t, rhs.s));
        t = rhs.t;
        c = rhs.c + std::max(0, s - rhs.s);
      }
    }
    else
    {
      if (rhs.c == -1)
      {
        s = lhs.s;
        t = std::max(rhs.s, std::min(rhs.t, lhs.t));
        c = lhs.c + std::max(0, lhs.t - t);
      }
      else
      {
        s = lhs.s;
        t = rhs.t;
        c = lhs.c + rhs.c + std::max(0, lhs.t - rhs.s);
      }
    }
  }

  int64_t answer() const
  {
    return c == -1 ? 0 : c;
  }

  void assign(node_t rhs)
  {
    *this = rhs;
  }
};

int main()
{
  int n = sc.next_int() - 1;
  int q = sc.next_int();

  cm::segment_tree<node_t> sa(n + 1);
  cm::segment_tree<node_t> sb(n + 1);
  for (int i = 0; i < n; i++)
  {
    int l  = sc.next_int();
    int r  = sc.next_int();
    int al = i, ar = i + 1;
    int bl = n - (i + 1), br = n - i;
    sa.modify(al, ar, &node_t::assign, node_t(l - al, r - ar));
    sb.modify(bl, br, &node_t::assign, node_t(l - bl, r - br));
  }

  for (int i = 0; i < q; i++)
  {
    int opt = sc.next_int();
    if (opt == 1)
    {
      int i  = sc.next_int() - 1;
      int l  = sc.next_int();
      int r  = sc.next_int();
      int al = i, ar = i + 1;
      int bl = n - (i + 1), br = n - i;
      sa.modify(al, ar, &node_t::assign, node_t(l - al, r - ar));
      sb.modify(bl, br, &node_t::assign, node_t(l - bl, r - br));
    }
    else
    {
      int s  = sc.next_int() - 1;
      int st = sc.next_int();
      int t  = sc.next_int() - 1;
      int tt = sc.next_int();

      if (s < t)
      {
        auto m = sa.query(s, t);
        m = node_t(node_t(st - s, st - s), m);
        m = node_t(m, node_t(tt - t, tt - t));
        printf("%" SCNi64 "\n", m.answer());
      }
      else if (s == t)
      {
        printf("%" SCNi64 "\n", std::max<int64_t>(st - tt, 0));
      }
      else
      {
        s = n - s;
        t = n - t;
        auto m = sb.query(s, t);
        m = node_t(node_t(st - s, st - s), m);
        m = node_t(m, node_t(tt - t, tt - t));
        printf("%" SCNi64 "\n", m.answer());
      }
    }
  }

  return 0;
}
