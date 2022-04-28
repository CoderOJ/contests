#include <bits/stdc++.h>

template <class T>
struct offset_ptr
{
  static T *base;

  uint32_t offset = -1;

  offset_ptr() = default;
  offset_ptr(T *p) : offset(p - base) {}
  offset_ptr(const offset_ptr &) = default;
  offset_ptr(offset_ptr &&) = default;
  offset_ptr &operator=(const offset_ptr &) = default;
  offset_ptr &operator=(offset_ptr &&) = default;

  offset_ptr &operator=(T *p)
  {
    offset = p - base;
    return *this;
  }

  T *operator->() const
  {
    return base + offset;
  }

  bool is_null() const 
  { 
    return offset == -1; 
  }
};

template <class T>
T *offset_ptr<T>::base = nullptr;

namespace trace_sgt
{

struct node_t;
using ptr_t = offset_ptr<node_t>;

#pragma pack(4)
struct node_t
{
  ptr_t ls, rs;
  int val;

  void push_down();
};

ptr_t new_node(int val)
{
  static node_t pool[1 << 26];
  static node_t *p = pool;
  static int set_base = [&]{
    offset_ptr<node_t>::base = pool;
    return 0;
  }();
  p->val = val;
  return p++;
}

void node_t::push_down()
{
  if (ls.is_null()) ls = new_node(val);
  if (rs.is_null()) rs = new_node(val);
}

ptr_t init_tree(int l, int r)
{
  if (r - l == 1)
    return new_node(-1);
  else
  {
    int m = l + (r - l) / 2;
    ptr_t res = new_node(-1);
    res->ls = init_tree(l, m);
    res->rs = init_tree(m, r);
    return res;
  }
}

ptr_t range_assign(ptr_t u, int l, int r, int ml, int mr, int v)
{
  if (ml <= l && r <= mr)
  {
    return new_node(v);
  }
  else
  {
    u->push_down();
    ptr_t res = new_node(v);
    int m = l + (r - l) / 2;
    if (ml < m) res->ls = range_assign(u->ls, l, m, ml, mr, v);
    else res->ls = u->ls;
    if (mr > m) res->rs = range_assign(u->rs, m, r, ml, mr, v);
    else res->rs = u->rs;
    return res;
  }
}

int position_query(ptr_t u, int l, int r, int qp)
{
  if (u->ls.is_null() || u->rs.is_null())
  {
    return u->val;
  }
  else
  {
    int m = l + (r - l) / 2;
    if (qp < m) return position_query(u->ls, l, m, qp);
    else return position_query(u->rs, m, r, qp);
  }
}

}

const int N = 500005;

struct sgt_t
{
  struct node_t
  {
    int sum;
    int len;
    int assign;

    node_t() = default;

    void push_up(const node_t &lhs, const node_t &rhs)
    {
      sum = lhs.sum + rhs.sum;
    }

    void push_assign(int val)
    {
      sum = len * val;
      assign = val;
    }

    void push_down(node_t &lhs, node_t &rhs)
    {
      if (assign != -1)
      {
        lhs.push_assign(assign);
        rhs.push_assign(assign);
        assign = -1;
      }
    }
  };

  node_t p[N * 4];

  void init(int u, int l, int r)
  {
    p[u].len = r - l;
    p[u].assign = -1;
    if (r - l > 1)
    {
      int m = l + (r - l) / 2;
      init(u + u, l, m);
      init(u + u + 1, m, r);
    }
  }

  void range_assign(int u, int l, int r, int ml, int mr, int v)
  {
    if (ml <= l && r <= mr)
    {
      p[u].push_assign(v);
    }
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int m = l + (r - l) / 2;
      if (ml < m) range_assign(u + u, l, m, ml, mr, v);
      if (mr > m) range_assign(u + u + 1, m, r, ml, mr, v);
      p[u].push_up(p[u + u], p[u + u + 1]);
    }
  }

  int range_query(int u, int l, int r, int ql, int qr)
  {
    if (ql <= l && r <= qr)
    {
      return p[u].sum;
    }
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int m = l + (r - l) / 2;
      if (qr <= m) return range_query(u + u, l, m, ql, qr);
      else if (ql >= m) return range_query(u + u + 1, m, r, ql, qr);
      else return range_query(u + u, l, m, ql, qr) + range_query(u + u + 1, m, r, ql, qr);
    }
  }
};

trace_sgt::ptr_t tp[N];
sgt_t sgt;
int op_val[N];

int main()
{
  int n, m, ty;
  scanf("%d%d%d", &n, &m, &ty);
  sgt.init(1, 0, n);
  tp[0] = trace_sgt::init_tree(0, n);

  int last_ans = 0;
  for (int i = 0; i < m; i++)
  {
    int opt;
    scanf("%d", &opt);
    if (opt == 1)
    {
      int l, r;
      scanf("%d%d", &l, &r);
      l = (l + last_ans * ty) % n + 1;
      r = (r + last_ans * ty) % n + 1;
      if (l > r) std::swap(l, r);
      l--;

      tp[i + 1] = tp[i];
      last_ans = sgt.range_query(1, 0, n, l, r);
      printf("%d\n", last_ans);
    }
    else if (opt == 2)
    {
      int l;
      scanf("%d", &l);
      l = (l + last_ans * ty) % n + 1;
      l--;

      int lp_id = trace_sgt::position_query(tp[i], 0, n, l);
      if (lp_id == -1)
      {
        tp[i + 1] = tp[i];
      }
      else
      {
        int llp_id = trace_sgt::position_query(tp[lp_id], 0, n, l);
        if (llp_id == -1)
          sgt.range_assign(1, 0, n, l, l + 1, 0);
        else
          sgt.range_assign(1, 0, n, l, l + 1, op_val[llp_id]);
        tp[i + 1] = trace_sgt::range_assign(tp[i], 0, n, l, l + 1, llp_id);
      }
    }
    else
    {
      int l, r;
      scanf("%d%d", &l, &r);
      l = (l + last_ans * ty) % n + 1;
      r = (r + last_ans * ty) % n + 1;
      if (l > r) std::swap(l, r);
      l--;
      int x;
      scanf("%d", &x);

      op_val[i] = x;
      sgt.range_assign(1, 0, n, l, r, x);
      tp[i + 1] = trace_sgt::range_assign(tp[i], 0, n, l, r, i);
    }
  }
  return 0;
}
