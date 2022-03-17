#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <limits>
#include <numeric>
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 200005, 5005)

struct sgt_time_t
{
  struct node_t
  {
    std::vector<std::pair<int, int64_t>> st;

    void push_back(int x, int64_t y)
    {
      while (st.size() >= 2)
      {
        const auto &[px, py]   = *(st.end() - 1);
        const auto &[ppx, ppy] = *(st.end() - 2);
        if ((py - y) * (ppx - px) < (ppy - py) * (px - x))
          break;
        st.pop_back();
      }
      while (st.size() >= 1 && st.back().first == x && st.back().second > y)
        st.pop_back();
      st.emplace_back(x, y);
    }

    size_t cur = 0;

    int64_t query(int64_t x)
    {
      while (cur + 1 < st.size())
      {
        int64_t v_cur  = st[cur].first * x + st[cur].second;
        int64_t v_next = st[cur + 1].first * x + st[cur + 1].second;
        if (v_cur < v_next)
          break;
        cur += 1;
      }
      if (cur >= st.size())
        return std::numeric_limits<int64_t>::max();
      else
        return st[cur].first * x + st[cur].second;
    }
  };

  node_t p[N * 4];

  void push_back(int u, int l, int r, int pos, int x, int64_t y)
  {
    p[u].push_back(x, y);
    if (r - l == 1) {}
    else
    {
      int m = l + (r - l) / 2;
      if (pos < m)
        push_back(u + u, l, m, pos, x, y);
      else
        push_back(u + u + 1, m, r, pos, x, y);
    }
  }

  int query(int u, int l, int r, int64_t x, int64_t v)
  {
    if (r - l == 1)
    {
      if (v >= p[u].query(x))
        return l;
      else
        return r;
    }
    else
    {
      int m = l + (r - l) / 2;
      if (v >= p[u + u].query(x))
        return query(u + u, l, m, x, v);
      else
        return query(u + u + 1, m, r, x, v);
    }
  }

  int l, r;

  void push_back(int pos, int x, int64_t y)
  {
    push_back(1, l, r, pos, x, y);
  }

  int query(int64_t x, int64_t v)
  {
    return query(1, l, r, x, v);
  }
};

sgt_time_t sgt_time;

int     n, m;
int64_t a[N];

std::vector<int> cover_id[N];

struct opt_t
{
  int     op;
  int64_t v;
  int     l, r;
};

opt_t op[N];

void calc_cover_time()
{
  sgt_time.l   = 0;
  sgt_time.r   = m;
  int op_2_cnt = 0;
  for (int i = 0; i < m; i++)
  {
    if (op[i].op == 1)
    {
      sgt_time.push_back(i, -op_2_cnt, op[i].v);
    }
    else if (op[i].op == 2)
    {
      op_2_cnt += 1;
    }
  }
  for (int i = 0; i < n; i++)
  {
    int t = sgt_time.query(i + 1, a[i]);
    cover_id[t].push_back(i);
  }
}

struct sgt_t
{
  struct node_t
  {
    int64_t uncovered_sp;
    int64_t uncovered_sum;
    int     covered_cnt;
    int64_t covered_sp;
    int64_t covered_sum;
    int64_t uncovered_add = 0;
    int64_t covered_add   = 0;
    int64_t covered_cover = -1;

    static node_t make_uncovered(int p, int64_t v)
    {
      node_t result;
      result.uncovered_sp  = p;
      result.uncovered_sum = v;
      result.covered_cnt   = 0;
      result.covered_sp    = 0;
      result.covered_sum   = 0;
      return result;
    }

    static node_t make_covered(int p, int64_t v)
    {
      node_t result;
      result.uncovered_sp  = 0;
      result.uncovered_sum = 0;
      result.covered_cnt   = 1;
      result.covered_sp    = p;
      result.covered_sum   = v;
      return result;
    }

    node_t() = default;
    node_t(const node_t lhs, const node_t rhs) :
        uncovered_sp(lhs.uncovered_sp + rhs.uncovered_sp),
        uncovered_sum(lhs.uncovered_sum + rhs.uncovered_sum),
        covered_cnt(lhs.covered_cnt + rhs.covered_cnt),
        covered_sp(lhs.covered_sp + rhs.covered_sp),
        covered_sum(lhs.covered_sum + rhs.covered_sum)
    {
    }

    void push_uncovered_add(int64_t det)
    {
      uncovered_add += det;
      uncovered_sum += det * uncovered_sp;
    }

    void push_covered_add(int64_t det)
    {
      covered_add += det;
      covered_sum += det * covered_sp;
    }

    void push_add(int64_t det)
    {
      push_uncovered_add(det);
      push_covered_add(det);
    }

    void push_covered_cover(int64_t val)
    {
      covered_add   = 0;
      covered_cover = val;
      covered_sum   = val * covered_cnt;
    }

    void push_down(node_t &lhs, node_t &rhs)
    {
      if (covered_cover != -1)
      {
        lhs.push_covered_cover(covered_cover);
        rhs.push_covered_cover(covered_cover);
        covered_cover = -1;
      }
      if (uncovered_add != 0)
      {
        lhs.push_uncovered_add(uncovered_add);
        rhs.push_uncovered_add(uncovered_add);
        uncovered_add = 0;
      }
      if (covered_add != 0)
      {
        lhs.push_covered_add(covered_add);
        rhs.push_covered_add(covered_add);
        covered_add = 0;
      }
    }
  };

  node_t p[N * 4];

  void assign(int u, int l, int r, int pos, node_t v)
  {
    if (r - l == 1)
    {
      p[u] = v;
    }
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int m = l + (r - l) / 2;
      if (pos < m)
        assign(u + u, l, m, pos, v);
      else
        assign(u + u + 1, m, r, pos, v);
      p[u] = node_t(p[u + u], p[u + u + 1]);
    }
  }

  void add(int u, int l, int r, int ml, int mr, int64_t det)
  {
    if (ml <= l && r <= mr)
    {
      p[u].push_add(det);
    }
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int m = l + (r - l) / 2;
      if (ml < m)
        add(u + u, l, m, ml, mr, det);
      if (mr > m)
        add(u + u + 1, m, r, ml, mr, det);
      p[u] = node_t(p[u + u], p[u + u + 1]);
    }
  }

  void cover(int u, int l, int r, int ml, int mr, int64_t det)
  {
    if (ml <= l && r <= mr)
    {
      p[u].push_covered_cover(det);
    }
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int m = l + (r - l) / 2;
      if (ml < m)
        cover(u + u, l, m, ml, mr, det);
      if (mr > m)
        cover(u + u + 1, m, r, ml, mr, det);
      p[u] = node_t(p[u + u], p[u + u + 1]);
    }
  }

  node_t query(int u, int l, int r, int ql, int qr)
  {
    if (ql <= l && r <= qr)
    {
      return p[u];
    }
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int m = l + (r - l) / 2;
      if (qr <= m)
        return query(u + u, l, m, ql, qr);
      else if (ql >= m)
        return query(u + u + 1, m, r, ql, qr);
      else
        return node_t(query(u + u, l, m, ql, qr),
                      query(u + u + 1, m, r, ql, qr));
    }
  }
};

sgt_t sgt;

bool use_sgt_cmp = false;

struct cmp_t
{
  bool operator()(int64_t x, int64_t y) const
  {
    if (!use_sgt_cmp)
      return x < y;
    else
    {
      int64_t xv = sgt.query(1, 0, n, (int)x, (int)x + 1).covered_sum;
      return xv < y;
    }
  }
};

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_long();
  for (int i = 0; i < m; i++)
  {
    op[i].op = sc.next_int();
    if (op[i].op == 1)
    {
      op[i].v = sc.next_long();
    }
    else if (op[i].op == 3)
    {
      op[i].l = sc.next_int() - 1;
      op[i].r = sc.next_int();
    }
  }

  calc_cover_time();

  for (int i = 0; i < n; i++)
  {
    sgt.assign(1, 0, n, i, sgt_t::node_t::make_uncovered(i + 1, a[i]));
  }

  std::set<int64_t, cmp_t> covered_ids;

  for (int i = 0; i < m; i++)
  {
    if (op[i].op == 1)
    {
      int64_t v       = op[i].v;
      use_sgt_cmp = true;
      auto it     = covered_ids.lower_bound(v);
      use_sgt_cmp = false;
      if (it != covered_ids.end())
      {
        int l = (int)*it;
        sgt.cover(1, 0, n, l, n, v);
      }
      for (int id : cover_id[i])
      {
        sgt.assign(1, 0, n, id, sgt_t::node_t::make_covered(id + 1, v));
        covered_ids.insert(id);
      }
    }
    else if (op[i].op == 2)
    {
      sgt.add(1, 0, n, 0, n, 1);
    }
    else
    {
      int  l   = op[i].l;
      int  r   = op[i].r;
      auto ans = sgt.query(1, 0, n, l, r);
      std::cout << ans.uncovered_sum + ans.covered_sum << std::endl;
    }
  }

  return 0;
}
