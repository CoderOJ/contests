#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 200005;

#include <vector>

namespace cm
{

template <bool _have_push_down = false>
struct segment_tree_node_base
{
  static constexpr bool have_push_down = false;
  segment_tree_node_base()             = default;
  segment_tree_node_base(int) {}
  segment_tree_node_base(const segment_tree_node_base &,
                         const segment_tree_node_base &)
  {
  }
  void push_down(segment_tree_node_base &, segment_tree_node_base &) {}
};

template <>
struct segment_tree_node_base<true>
{
  static constexpr bool have_push_down = true;
  segment_tree_node_base()             = default;
  segment_tree_node_base(int) {}
  segment_tree_node_base(const segment_tree_node_base &,
                         const segment_tree_node_base &)
  {
  }
};

template <class _NodeType>
struct segment_tree
{
protected:
  int                    l = 0, r = 0;
  std::vector<_NodeType> p;

  void _init(int u, int l, int r)
  {
    if (r - l == 1)
    {
      p[u] = _NodeType(l);
    }
    else
    {
      int _mid = l + (r - l) / 2;
      _init(u + 1, l, _mid);
      _init(u + (_mid - l) * 2, _mid, r);
      p[u] = _NodeType(p[u + 1], p[u + (_mid - l) * 2]);
    }
  }

  void _modify(int u, int l, int r, int ml, int mr)
  {
    if (ml <= l && r <= mr)
    {
      p[u].push_assign();
    }
    else
    {
      int _mid = l + (r - l) / 2;
      if (_NodeType::have_push_down)
        p[u].push_down(p[u + 1], p[u + (_mid - l) * 2]);
      if (ml < _mid)
        _modify(u + 1, l, _mid, ml, mr);
      if (mr > _mid)
        _modify(u + (_mid - l) * 2, _mid, r, ml, mr);
      p[u] = _NodeType(p[u + 1], p[u + (_mid - l) * 2]);
    }
  }

  _NodeType _query(int u, int l, int r, int ql, int qr)
  {
    if (ql <= l && r <= qr)
    {
      return p[u];
    }
    else
    {
      int _mid = l + (r - l) / 2;
      if (_NodeType::have_push_down)
        p[u].push_down(p[u + 1], p[u + (_mid - l) * 2]);
      if (qr <= _mid)
        return _query(u + 1, l, _mid, ql, qr);
      else if (ql >= _mid)
        return _query(u + (_mid - l) * 2, _mid, r, ql, qr);
      else
        return _NodeType(_query(u + 1, l, _mid, ql, qr),
                         _query(u + (_mid - l) * 2, _mid, r, ql, qr));
    }
  }

public:
  segment_tree() = default;
  explicit segment_tree(int r) : l(0), r(r), p((r - l) * 2 - 1)
  {
    _init(0, l, r);
  }
  segment_tree(int l, int r) : l(l), r(r), p((r - l) * 2 - 1)
  {
    _init(0, l, r);
  }

  void modify(int ml, int mr)
  {
#ifdef CM_DEBUG_H
    cm_assert(ml >= l, l, r, ml, mr);
    cm_assert(mr <= r, l, r, ml, mr);
    cm_assert(ml < mr, l, r, ml, mr);
#endif
    _modify(0, l, r, ml, mr);
  }

  _NodeType query(int ql, int qr)
  {
#ifdef CM_DEBUG_H
    cm_assert(ql >= l, l, r, ql, qr);
    cm_assert(qr <= r, l, r, ql, qr);
    cm_assert(ql < qr, l, r, ql, qr);
#endif
    return _query(0, l, r, ql, qr);
  }
};

} // namespace cm

struct node_t : public cm::segment_tree_node_base<true>
{
  using cm::segment_tree_node_base<true>::segment_tree_node_base;

  int sum = 1;
  int id  = 0;

  node_t(int id) : id(id) {}
  node_t(const node_t lhs, const node_t rhs) :
      sum(lhs.sum + rhs.sum), id(lhs.sum ? lhs.id : rhs.id)
  {
  }

  void push_assign()
  {
    sum = 0;
  }

  void push_down(node_t &lhs, node_t &rhs)
  {
    if (sum == 0)
    {
      lhs.push_assign();
      rhs.push_assign();
    }
  }
};

struct opt_t
{
  int type;
  int l, r;
  int p;
  int ans;
  int id;

  int cl, cr, cm;
};

opt_t ops[N];
int   n, q;

int min_determ[N];

int main()
{
  n = sc.next_int();
  q = sc.next_int();

  cm::segment_tree<node_t> imm(n);

  for (int i = 0; i < q; i++)
  {
    ops[i].id   = i;
    ops[i].type = sc.next_int();
    if (ops[i].type == 0)
    {
      ops[i].l = sc.next_int() - 1;
      ops[i].r = sc.next_int();
      ops[i].p = sc.next_int();
      if (ops[i].p == 0)
      {
        imm.modify(ops[i].l, ops[i].r);
      }
    }
    else
    {
      ops[i].p = sc.next_int() - 1;
      if (imm.query(ops[i].p, ops[i].p + 1).sum == 0)
        ops[i].ans = 1;
    }
  }

  for (int i = 0; i < q; i++)
    if (ops[i].type == 0 && ops[i].p == 1)
    {
      ops[i].cl = 0;
      ops[i].cr = q;
    }

  std::fill(min_determ, min_determ + n, 0x3f3f3f3f);

  while (std::any_of(ops, ops + q, [](const opt_t &op) {
    return op.type == 0 && op.p == 1 && op.cl < op.cr;
  }))
  {
    cm::segment_tree<node_t> sgt(n);

    std::vector<opt_t *> qs;
    for (int i = 0; i < q; i++)
      if (ops[i].type == 0 && ops[i].p == 1)
      {
        ops[i].cm = (ops[i].cl + ops[i].cr) / 2;
        qs.push_back(&ops[i]);
      }
    std::sort(qs.begin(), qs.end(), [](const opt_t *a, const opt_t *b) {
      return a->cm < b->cm;
    });

    int op_id = 0;
    for (const auto &q : qs)
    {
      while (op_id <= q->cm)
      {
        if (ops[op_id].type == 0 && ops[op_id].p == 0)
          sgt.modify(ops[op_id].l, ops[op_id].r);
        op_id++;
      }
      auto res = sgt.query(q->l, q->r);
      see(res.sum, res.id);
      if (res.sum <= 1)
      {
        q->cr = q->cm;

        int min_time = std::max(q->cm, q->id);
        check_min(min_determ[res.id], min_time);
      }
      else
      {
        q->cl = q->cm + 1;
      }
    }
  }

  for (int i = 0; i < q; i++)
    if (ops[i].type == 1)
    {
      if (ops[i].ans == 1)
        puts("NO");
      else
      {
        see(min_determ[ops[i].p]);
        if (min_determ[ops[i].p] <= i)
          puts("YES");
        else
          puts("N/A");
      }
    }

  return 0;
}