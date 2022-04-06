#include <bits/stdc++.h>

const int N = 100005;
const int V = 100000;

int n, m;
int64_t x0;
int gen() 
{
	x0 = (100000005 * x0 + 20150609) % 998244353;
	return static_cast<int>(x0 / 100);
}

struct sgt_t
{
  struct node_t
  {
    int min, max;
    bool flip = false;

    node_t() = default;
    node_t(int v) : min(v), max(v) {}
    node_t(node_t lhs, node_t rhs) : min(std::min(lhs.min, rhs.min)), max(std::max(lhs.max, rhs.max)) {}

    void push_flip()
    {
      std::tie(min, max) = std::make_pair(V - max, V - min);
      flip = !flip;
    }

    void push_down(node_t &lhs, node_t &rhs)
    {
      if (flip)
      {
        lhs.push_flip();
        rhs.push_flip();
        flip = false;
      }
    }
  };

  node_t p[N * 4];

  void assign(int u, int l, int r, int pos, node_t val)
  {
    if (r - l == 1)
    {
      p[u] = val;
    }
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int m = l + (r - l) / 2;
      if (pos < m) assign(u + u, l, m, pos, val);
      else assign(u + u + 1, m, r, pos, val);
      p[u] = node_t(p[u + u], p[u + u + 1]);
    }
  }

  void flip(int u, int l, int r, int ml, int mr)
  {
    if (ml <= l && r <= mr)
    {
      p[u].push_flip();
    }
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int m = l + (r - l) / 2;
      if (ml < m) flip(u + u, l, m, ml, mr);
      if (mr > m) flip(u + u + 1, m, r, ml, mr);
      p[u] = node_t(p[u + u], p[u + u + 1]);
    }
  }

  int64_t query_segment(int u, int l, int r, auto f, int pmax = -1)
  {
    // printf("query_segment: [%d] [%d, %d) pmax = %d, p[u].max = %d\n", u, l, r, pmax, p[u].max);
    int64_t res = 0;
    if (p[u].max > pmax)
    {
      if (r - l == 1)
        res = f(r, p[u].max);
      else
      {
        p[u].push_down(p[u + u], p[u + u + 1]);
        int m = l + (r - l) / 2;
        res = std::max(res, query_segment(u + u + 1, m, r, f, pmax));
        res = std::max(res, query_segment(u + u, l, m, f, std::max(p[u + u + 1].max , pmax)));
      }
    }
    return res;
  }

  int query_max(int u, int l, int r, int ql, int qr)
  {
    if (ql >= qr) return -1;
    if (ql <= l && r <= qr) return p[u].max;
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int m = l + (r - l) / 2;
      if (qr <= m) return query_max(u + u, l, m, ql, qr);
      else if (ql >= m) return query_max(u + u + 1, m, r, ql, qr);
      else return std::max(query_max(u + u, l, m, ql, qr), query_max(u + u + 1, m, r, ql, qr));
    }
  }

  int64_t query(int u, int l, int r, int ql, int qr, auto f)
  {
    if (ql <= l && r <= qr)
      return query_segment(u, l, r, f, query_max(1, 0, n, r, qr));
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int m = l + (r - l) / 2;
      if (qr <= m) return query(u + u, l, m, ql, qr, f);
      else if (ql >= m) return query(u + u + 1, m, r, ql, qr, f);
      else return std::max(query(u + u, l, m, ql, qr, f), query(u + u + 1, m, r, ql, qr, f));
    }
  }
};

sgt_t t;

int main()
{
  scanf("%d%d%" SCNi64, &n, &m, &x0);
  for (int i = 0; i < n; i++)
    t.assign(1, 0, n, i, gen() % (V + 1));
  for (int i = 0; i < m; i++)
  {
    char c;
    scanf(" %c", &c);
    if (c == 'C')
    {
      int p = gen() % n;
      int v = gen() % (V + 1);
      t.assign(1, 0, n, p, v);
    }
    else if (c == 'R')
    {
      int l = gen() % n;
      int r = gen() % n;
      if (l > r) std::swap(l, r);
      r++;
      t.flip(1, 0, n, l, r);
    }
    else
    {
      int l = gen() % n;
      int r = gen() % n;
      if (l > r) std::swap(l, r);
      r++;
      int64_t a, b, c;
      scanf("%" SCNi64 "%" SCNi64 "%" SCNi64, &a, &b, &c);
      int64_t ans = t.query(1, 0, n, l, r, [a, b, c](int x, int y) {
        // printf("(%d, %d)\n", x, y);
        return a * x + b * y + c * x * y;
      });
      printf("%" SCNi64 "\n", ans);
    }
  }
  return 0;
}
