#include <bits/stdc++.h>

const int N = 500005;
const int INF = 2e9;

struct sgt_t
{
  struct node_t
  {
    int min;
    int sem;
    int hmin;

    int add = 0;
    int add_hmin = 0;
    int min_add = 0;
    int min_add_hmin = 0;

    node_t() = default;
    node_t(int val)
    {
      min = val;
      sem = INF;
      hmin = val;
    }
    node_t(const node_t &lhs, const node_t &rhs)
    {
      min = std::min(lhs.min, rhs.min);
      if (lhs.min == rhs.min) sem = std::min(lhs.sem, rhs.sem);
      else sem = std::min({lhs.sem, rhs.sem, std::max(lhs.min, rhs.min)});
      hmin = std::min(lhs.hmin, rhs.hmin);
    }

    void push_add(int det, int det_hmin)
    {
      add_hmin = std::min(add_hmin, add + det_hmin);
      add += det;
      hmin = std::min(hmin, sem + det_hmin);
      if (sem != INF) sem += det;
    }

    void push_min_add(int det, int det_hmin)
    {
      min_add_hmin = std::min(min_add_hmin, min_add + det_hmin);
      min_add += det;
      hmin = std::min(hmin, min + det_hmin);
      min += det;
    }

    void push_down(node_t &lhs, node_t &rhs)
    {
      bool is_min_lhs = lhs.min <= rhs.min;
      bool is_min_rhs = rhs.min <= lhs.min;
      lhs.push_add(add, add_hmin);
      if (is_min_lhs)
        lhs.push_min_add(min_add, min_add_hmin);
      else
        lhs.push_min_add(add, add_hmin);
      rhs.push_add(add, add_hmin);
      if (is_min_rhs)
        rhs.push_min_add(min_add, min_add_hmin);
      else
        rhs.push_min_add(add, add_hmin);
      add = 0;
      add_hmin = 0;
      min_add = 0;
      min_add_hmin = 0;
    }
  };

  node_t p[N * 4];

  void init(int u, int l, int r, int a[])
  {
    if (r - l == 1)
    {
      p[u] = node_t(a[l]);
    }
    else
    {
      int m = l + (r - l) / 2;
      init(u + u, l, m, a);
      init(u + u + 1, m, r, a);
      p[u] = node_t(p[u + u], p[u + u + 1]);
    }
  }

  void all_add(int u, int l, int r, int ml, int mr, int det)
  {
    if (ml <= l && r <= mr)
    {
      p[u].push_add(det, det);
      p[u].push_min_add(det, det);
    }
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int m = l + (r - l) / 2;
      if (ml < m) all_add(u + u, l, m, ml, mr, det);
      if (mr > m) all_add(u + u + 1, m, r, ml, mr, det);
      p[u] = node_t(p[u + u], p[u + u + 1]);
    }
  }

  void check_max(int u, int l, int r, int ml, int mr, int val)
  {
    if (ml <= l && r <= mr)
    {
      if (val <= p[u].min)
        return;
      else if (val < p[u].sem)
      {
        p[u].push_min_add(val - p[u].min, val - p[u].min);
        return;
      }
    }
    p[u].push_down(p[u + u], p[u + u + 1]);
    int m = l + (r - l) / 2;
    if (ml < m) check_max(u + u, l, m, ml, mr, val);
    if (mr > m) check_max(u + u + 1, m, r, ml, mr, val);
    p[u] = node_t(p[u + u], p[u + u + 1]);
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
      return node_t(query(u + u, l, m, ql, qr), query(u + u + 1, m, r, ql, qr));
    }
  }
};

sgt_t t;
int a[N], n, m;

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  t.init(1, 0, n, a);
  for (int i = 0; i < m; i++)
  {
    int opt;
    scanf("%d", &opt);
    if (opt == 1)
    {
      int l, r, c;
      scanf("%d%d%d", &l, &r, &c);
      l--;
      t.all_add(1, 0, n, l, r, c);
    }
    else if (opt == 2)
    {
      int l, r, c;
      scanf("%d%d%d", &l, &r, &c);
      l--;
      t.check_max(1, 0, n, l, r, c);
    }
    else if (opt == 3)
    {
      int l, r;
      scanf("%d%d", &l, &r);
      l--;
      auto res = t.query(1, 0, n, l, r);
      printf("%d\n", res.min);
    }
    else
    {
      int l, r;
      scanf("%d%d", &l, &r);
      l--;
      auto res = t.query(1, 0, n, l, r);
      printf("%d\n", res.hmin);
    }
  }
  return 0;
}
