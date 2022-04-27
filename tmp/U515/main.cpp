#include <bits/stdc++.h>

const int N = 1000005;

int read()
{
  int c = getchar_unlocked();
  while (!std::isdigit(c))
    c = getchar_unlocked();
  int r = 0;
  while (std::isdigit(c))
  {
    r = r * 10 + (c - '0');
    c = getchar_unlocked();
  }
  return r;
}

struct sgt_t
{
  struct node_t
  {
    int max = 0;
    int sem = 0;
    int mv = 0;

    void push_up(const node_t &lhs, const node_t &rhs)
    {
      if (lhs.max > rhs.max)
      {
        max = lhs.max;
        sem = std::max(lhs.sem, rhs.max);
      }
      else if (lhs.max == rhs.max)
      {
        max = lhs.max;
        sem = std::max(lhs.sem, rhs.sem);
      }
      else
      {
        max = rhs.max;
        sem = std::max(lhs.max, rhs.sem);
      }
    }

    void push_max_assign(int d)
    {
      max = d;
    }

    void push_mv_add(int d)
    {
      mv += d;
    }

    void push_down(node_t &lhs, node_t &rhs)
    {
      if (mv)
      {
        if (lhs.max > max)
        {
          lhs.max = max;
          lhs.mv += mv;
        }
        if (rhs.max > max)
        {
          rhs.max = max;
          rhs.mv += mv;
        }
        mv = 0;
      }
    }
  };

  node_t p[N * 2];

  void init(int u, int l, int r)
  {
    if (r - l == 1)
    {
      p[u].max = 0x3f3f3f3f;
    }
    else
    {
      int m = l + (r - l) / 2;
      init(u + 1, l, m);
      init(u + (m - l) * 2, m, r);
      p[u].push_up(p[u + 1], p[u + (m - l) * 2]);
    }
  }

  void range_check_min(int u, int l, int r, int ml, int mr, int v)
  {
    if (p[u].max > v)
    {
      if (ml <= l && r <= mr && p[u].sem <= v)
      {
        p[u].push_max_assign(v);
        p[u].push_mv_add(1);
      }
      else
      {
        int m = l + (r - l) / 2;
        p[u].push_down(p[u + 1], p[u + (m - l) * 2]);
        if (ml < m) range_check_min(u + 1, l, m, ml, mr, v);
        if (mr > m) range_check_min(u + (m - l) * 2, m, r, ml, mr, v);
        p[u].push_up(p[u + 1], p[u + (m - l) * 2]);
      }
    }
  }

  int query_mv(int u, int l, int r, int qp)
  {
    if (r - l == 1)
    {
      return p[u].mv;
    }
    else
    {
      int m = l + (r - l) / 2;
      p[u].push_down(p[u + 1], p[u + (m - l) * 2]);
      if (qp < m) return query_mv(u + 1, l, m, qp);
      else return query_mv(u + (m - l) * 2, m, r, qp);
    }
  }
};

sgt_t sgt;

int a[N], t[N];
int n, q;
std::vector<std::tuple<int, int, int>> modifies[N];
std::vector<int> queries[N];
int ans[N];

int main()
{
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &a[i]);
    t[i] = -1;
  }
  for (int i = 0; i < q; i++)
  {
    int op;
    scanf("%d", &op);
    if (op == 1)
    {
      int p, v;
      scanf("%d%d", &p, &v);
      p--;
      modifies[p].emplace_back(t[p], i, a[p]);
      t[p] = i;
      a[p] = v;
    }
    else
    {
      int p;
      scanf("%d", &p);
      p--;
      queries[p].push_back(i);
    }
  }
  for (int i = 0; i < n; i++)
    modifies[i].emplace_back(t[i], q, a[i]);

  sgt.init(1, -1, q);
  for (int i = n - 1; i >= 0; i--)
  {
    for (const auto &[tl, tr, v] : modifies[i])
      sgt.range_check_min(1, -1, q, tl, tr, v);
    for (int p : queries[i])
      ans[p] = sgt.query_mv(1, -1, q, p);
  }

  for (int i = 0; i < q; i++)
    if (ans[i])
      printf("%d\n", ans[i]);

  return 0;
}
