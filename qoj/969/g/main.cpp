#include <bits/stdc++.h>
#include <limits>
#include <vector>

constexpr int64_t INF = std::numeric_limits<int64_t>::max() / 8;

struct node_t
{
  int64_t p = 0, h = 0, l = 0;

  node_t() = default;

  node_t(int64_t p, int64_t h, int64_t l) :
      p(std::min(INF, p)), h(std::min(INF, h)), l(std::min(INF, l))
  {
  }
};

node_t join(const node_t &a, const node_t &b)
{
  if (a.h < b.p)
    return {b.p + (a.p + a.l - a.h), b.h, b.l};
  else if (a.h < b.p + b.l)
    return {a.p, b.h, a.l + (b.p + b.l - a.h)};
  else
    return {a.p, b.h + (a.h - b.p - b.l), a.l};
}

struct segment_tree
{
  std::vector<node_t> p;

  segment_tree(int n) : p(4l * n) {}

  void init(int u, int l, int r, const std::vector<node_t> &a)
  {
    if (r - l == 1)
      p[u] = a[l];
    else
    {
      int m = l + (r - l) / 2;
      init(u + u, l, m, a);
      init(u + u + 1, m, r, a);
      p[u] = join(p[u + u], p[u + u + 1]);
    }
  }

  void modify(int u, int l, int r, int pos, const node_t &v)
  {
    if (r - l == 1)
      p[u] = v;
    else
    {
      int m = l + (r - l) / 2;
      if (pos < m)
        modify(u + u, l, m, pos, v);
      else
        modify(u + u + 1, m, r, pos, v);
      p[u] = join(p[u + u], p[u + u + 1]);
    }
  }

  std::pair<node_t, int> lower_bound(
      int u, int l, int r, int pl, const node_t &prev, const auto &pred)
  {
    if (pl <= l)
    {
      auto vv = join(prev, p[u]);
      if (pred(vv))
        return {vv, r};
    }

    if (r - l == 1)
      return {prev, l};
    else
    {
      int m = l + (r - l) / 2;
      if (m <= pl)
      {
        return lower_bound(u + u + 1, m, r, pl, prev, pred);
      }
      else
      {
        auto la = lower_bound(u + u, l, m, pl, prev, pred);
        if (la.second < m)
          return la;
        else
          return lower_bound(u + u + 1, m, r, pl, la.first, pred);
      }
    }
  }
};

int main()
{
  int t;
  scanf("%d", &t);

  for (int i = 0; i < t; i++)
  {
    int n, q;
    scanf("%d%d", &n, &q);
    int64_t h;
    scanf("%" SCNi64, &h);

    auto read_node = [] -> node_t {
      char type;
      scanf(" %c", &type);
      int64_t v;
      scanf("%" SCNi64, &v);

      if (type == 'B')
        return {v + 1, 1, 0};
      else if (type == 'K')
        return {v, v, INF};
      else
        return {0, v, v};
    };

    std::vector<node_t> as(n);
    for (int i = 0; i < n; i++)
      as[i] = read_node();

    segment_tree sgt(n);
    sgt.init(1, 0, n, as);

    for (int i = 0; i < q; i++)
    {
      char opt;
      scanf(" %c", &opt);

      if (opt == 'Z')
      {
        int p;
        scanf("%d", &p);
        p -= 1;
        auto v = read_node();
        sgt.modify(1, 0, n, p, v);
      }
      else
      {
        int pl;
        scanf("%d", &pl);
        pl -= 1;

        // clang-format off
        int pr = sgt.lower_bound(1, 0, n, pl, {0, 0, 0}, [h](const node_t &v) {
          return h >= v.p;
        }).second;
        // clang-format on

        if (pl == pr)
          puts("-1");
        else
          printf("%d\n", pr);
      }
    }
  }

  return 0;
}
