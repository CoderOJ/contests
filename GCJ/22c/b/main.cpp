#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

#ifndef CM_SEGMENT_TREE
#define CM_SEGMENT_TREE

#include <vector>

namespace cm
{

template <bool _have_push_down = false>
struct segment_tree_node_base
{
  static constexpr bool have_push_down = false;
  segment_tree_node_base()             = default;
  explicit segment_tree_node_base(int) {}
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
  explicit segment_tree_node_base(int) {}
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

  template <class... _Param>
  void _modify(int u, int l, int r, int ml, int mr, _Param... _param)
  {
    if (ml <= l && r <= mr)
    {
      p[u].push_add(_param...);
    }
    else
    {
      int _mid = l + (r - l) / 2;
      if (_NodeType::have_push_down)
        p[u].push_down(p[u + 1], p[u + (_mid - l) * 2]);
      if (ml < _mid)
        _modify(u + 1, l, _mid, ml, mr, _param...);
      if (mr > _mid)
        _modify(u + (_mid - l) * 2, _mid, r, ml, mr, _param...);
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

  template <class _Pred>
  int _lower_bound(int u, int l, int r, _Pred _pred, _NodeType _prev)
  {
    if (r - l == 1)
    {
      return l;
    }
    else
    {
      int _mid = l + (r - l) / 2;
      if (_NodeType::have_push_down)
        p[u].push_down(p[u + 1], p[u + (_mid - l) * 2]);
      _NodeType _attempt = _NodeType(_prev, p[u + 1]);
      if (_pred(_attempt))
        return _lower_bound(u + (_mid - l) * 2, _mid, r, _pred, _attempt);
      else
        return _lower_bound(u + 1, l, _mid, _pred, _prev);
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

  template <class... _Param>
  void modify(int ml,
              int mr,
              _Param... _param)
  {
#ifdef CM_DEBUG_H
    cm_assert(ml >= l, l, r, ml, mr);
    cm_assert(mr <= r, l, r, ml, mr);
    cm_assert(ml < mr, l, r, ml, mr);
#endif
    if (ml < mr)
      _modify(0, l, r, ml, mr, _param...);
  }

  _NodeType query(int ql, int qr)
  {
#ifdef CM_DEBUG_H
    cm_assert(ql >= l, l, r, ql, qr);
    cm_assert(qr <= r, l, r, ql, qr);
    cm_assert(ql <= qr, l, r, ql, qr);
#endif
    if (ql >= qr)
      return _NodeType();
    else
      return _query(0, l, r, ql, qr);
  }

  template <class _Pred>
  int lower_bound(_Pred _pred, _NodeType _prev = _NodeType())
  {
    if (_pred(p[0]))
      return r;
    else
      return _lower_bound(0, l, r, _pred, _prev);
  }
};

} // namespace cm

#endif

struct node_t : public cm::segment_tree_node_base<true>
{
  using cm::segment_tree_node_base<true>::segment_tree_node_base;

  int max     = 0;
  int max_cnt = 1;
  int add     = 0;

  node_t() = default;
  node_t(const node_t &lhs, const node_t &rhs) :
      max(std::max(lhs.max, rhs.max)),
      max_cnt((lhs.max == max ? lhs.max_cnt : 0) +
              (rhs.max == max ? rhs.max_cnt : 0))
  {
  }

  void push_add(int det)
  {
    add += det;
    max += det;
  }

  void push_down(node_t &lhs, node_t &rhs)
  {
    if (add != 0)
    {
      lhs.push_add(add);
      rhs.push_add(add);
      add = 0;
    }
  }
};

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    printf("Case #%d: ", i + 1);

    int n = sc.next_int();
    int c = sc.next_int();

    std::vector<std::pair<int, int>> c_inter(c);
    for (int i = 0; i < c; i++)
    {
      c_inter[i].first  = sc.next_int();
      c_inter[i].second = sc.next_int() + 1;
    }

    std::vector<int> a(n + n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int() - 1;
    std::copy(a.begin(), a.begin() + n, a.begin() + n);

    std::vector<std::vector<int>> occur(c, {-1});
    for (int i = 0; i < n; i++)
      occur[a[i]].push_back(i);

    cm::segment_tree<node_t> sgt(0, n + n);
    auto set = [&](const std::vector<int> &occur, int cl, int cr, int det) {
      if (cl == 0)
        cl = 1;

      if (occur.back() + 1 < n + n)
        sgt.modify(occur.back() + 1, n + n, det);

      int vl = static_cast<int>(occur.size()) >= cr
                   ? occur[occur.size() - cr] + 1
                   : 0;
      int vr = static_cast<int>(occur.size()) >= cl
                   ? occur[occur.size() - cl] + 1
                   : 0;
      if (vl != vr)
        sgt.modify(vl, vr, det);
    };

    for (int i = 0; i < c; i++)
      set(occur[i], c_inter[i].first, c_inter[i].second, 1);

    int64_t ans = 0;
    for (int r = n; r < n + n; r++)
    {
      auto res = sgt.query(r - n + 1, r - 1);
      if (res.max == c)
        ans += res.max_cnt;
      // see(r, ans);

      int cid = a[r];
      set(occur[cid], c_inter[cid].first, c_inter[cid].second, -1);
      occur[cid].push_back(r);
      set(occur[cid], c_inter[cid].first, c_inter[cid].second, 1);
    }

    std::cout << ans << std::endl;
  }
  return 0;
}
