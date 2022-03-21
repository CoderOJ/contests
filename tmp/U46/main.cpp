#include <bits/stdc++.h>

const int N = 100005;

int type, n, m, q, a[N];

struct info_t
{
  int a, b;
  info_t(int a = 1, int b = 0) : a(a), b(b) {}
};

info_t join(info_t lhs, info_t rhs)
{
  return info_t(1ll * lhs.a * rhs.a % m, (1ll * lhs.b * rhs.a + rhs.b) % m);
}

struct sgt_t
{
  struct update_t
  {
    int l, r;
    info_t e;

    bool operator< (int p) { return r <= p; }
  };

  struct node_t
  {
    bool filled = false;
    std::vector<update_t> updates;

    void push_up(const node_t &lhs, const node_t &rhs)
    {
      if (lhs.filled && rhs.filled)
      {
        filled = true;
        updates.clear();

        // puts("lhs:"); for (auto p : lhs.updates) printf("{%d, %d, {%d, %d}}\n", p.l, p.r, p.e.a, p.e.b);
        // puts("rhs:"); for (auto p : rhs.updates) printf("{%d, %d, {%d, %d}}\n", p.l, p.r, p.e.a, p.e.b);

        std::vector<int> brks;
        for (auto p : lhs.updates) brks.push_back(p.l), brks.push_back(p.r);
        for (auto p : rhs.updates) brks.push_back(p.l), brks.push_back(p.r);
        std::sort(brks.begin(), brks.end()); brks.erase(std::unique(brks.begin(), brks.end()), brks.end());

        auto lhs_it = lhs.updates.begin();
        auto rhs_it = rhs.updates.begin();
        for (size_t i = 0; i + 1 < brks.size(); i++)
        {
          int cl = brks[i], cr = brks[i + 1];
          while (lhs_it != lhs.updates.end() && lhs_it->r <= cl) lhs_it++;
          while (rhs_it != rhs.updates.end() && rhs_it->r <= cl) rhs_it++;
          if (lhs_it != lhs.updates.end() && lhs_it->l <= cl && cr <= lhs_it->r) {
            if (rhs_it != rhs.updates.end() && rhs_it->l <= cl && cr <= rhs_it->r)
              updates.push_back({cl, cr, join(lhs_it->e, rhs_it->e)}); 
            else 
              updates.push_back({cl, cr, lhs_it->e}); }
          else {
            if (rhs_it != rhs.updates.end() && rhs_it->l <= cl && cr <= rhs_it->r)
              updates.push_back({cl, cr, rhs_it->e}); }
        }

        // puts("sum:"); for (auto p : updates) printf("{%d, %d, {%d, %d}}\n", p.l, p.r, p.e.a, p.e.b);
      }
    }

    info_t query(int p)
    {
      auto it = std::lower_bound(updates.begin(), updates.end(), p); 
      if (it != updates.end() && it->l <= p && p < it->r) return it->e;
      else return info_t();
    }
  };

  node_t p[N * 4];

  void modify(int u, int l, int r, int pos, update_t upd)
  {
    if (r - l == 1)
    {
      p[u].filled = true;
      p[u].updates.push_back(upd);
    }
    else
    {
      int m = l + (r - l) / 2;
      if (pos < m)
        modify(u + u, l, m, pos, upd);
      else
        modify(u + u + 1, m, r, pos, upd);
      p[u].push_up(p[u + u], p[u + u + 1]);
    }
  }

  info_t query(int u, int l, int r, int ql, int qr, int qp)
  {
    // printf("query: %d(%d, %d), (%d, %d)\n", u, l, r, ql, qr);
    if (ql <= l && r <= qr)
    {
      auto res = p[u].query(qp);
      // printf("query: (%d, %d) -> {%d, %d}\n", l, r, res.a, res.b);
      return res;
    }
    else
    {
      int m = l + (r - l) / 2;
      if (qr <= m)
        return query(u + u, l, m, ql, qr, qp);
      else if (ql >= m)
        return query(u + u + 1, m, r, ql, qr, qp);
      else
        return join(query(u + u, l, m, ql, qr, qp),
                    query(u + u + 1, m, r, ql, qr, qp));
    }
  }
};

sgt_t sgt;

int main()
{
  scanf("%d%d%d", &type, &n, &m);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  scanf("%d", &q);
  int update_id = 0, last_ans = 0;
  for (int i = 0; i < q; i++)
  {
    if ((type & 1) == 0) last_ans = 0;
    int opt; scanf("%d", &opt);
    if (opt == 1)
    {
      int l, r, a, b; scanf("%d%d%d%d", &l, &r, &a, &b); l^=last_ans, r^=last_ans, l--;
      sgt.modify(1, 0, N, update_id++, {l, r, {a, b}});
    }
    else
    {
      int l, r, k; scanf("%d%d%d", &l, &r, &k); l^=last_ans, r^=last_ans, k^=last_ans, l--; k--;
      info_t e = sgt.query(1, 0, N, l, r, k);
      last_ans = (1ll * e.a * a[k] + e.b) % m;
      printf("%d\n", last_ans);
    }
  }

  return 0;
}
