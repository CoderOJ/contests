#include <bits/stdc++.h>

const int N = 300005;
const int B = 20;

std::vector<std::pair<int, int>> e[N];

int n, m;
int dep[N];
int dis[N];

int dfn[N], dfn_cur;
int st[B + 1][N * 2];

void dfs(int u, int fa = 0)
{
  dep[u]         = dep[fa] + 1;
  dfn[u]         = ++dfn_cur;
  st[0][dfn_cur] = u;

  for (auto p : e[u])
  {
    int v = p.first, w = p.second;
    if (v != fa)
    {
      dis[v] = dis[u] + w;
      dfs(v, u);
      st[0][++dfn_cur] = u;
    }
  }
}

bool cmp_dep(int x, int y)
{
  return dep[x] < dep[y];
}

void init_st()
{
  for (int j = 1; j <= B; ++j)
    for (int i = 1; i + (1 << j) - 1 <= dfn_cur; ++i)
      st[j][i] = std::min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))], cmp_dep);
}

int query(int l, int r)
{
  int t = 31 - __builtin_clz(r - l + 1);
  return std::min(st[t][l], st[t][r - (1 << t) + 1], cmp_dep);
}

int lca(int u, int v)
{
  if (dfn[u] > dfn[v])
    std::swap(u, v);
  return query(dfn[u], dfn[v]);
}

int distance(int u, int v)
{
  return dis[u] + dis[v] - 2 * dis[lca(u, v)];
}

int buf[50000000], *buf_top = buf;

int *allocate(int n)
{
  auto res = buf_top;
  buf_top += n;
  return res;
}

class vtree_t
{
  static const int INF = 0x3f3f3f3f;

public:
  int n, m;

  int *nd, *fa, *f, *g, *id;

  vtree_t() = default;

  vtree_t(const std::vector<int> &a)
  {
    n = m = (int)a.size();
    nd    = allocate(m);
    for (int i = 0; i < m; ++i)
      nd[i] = a[i];

    static int sta[N];
    int        top = 0;

    static std::vector<std::pair<int, int>> e[N];
    for (int i = 0; i < m; ++i)
      e[i].clear();

    auto add = [&](int u) {
      if (!top)
      {
        sta[top++] = u;
        return;
      }
      int x = sta[top - 1], y, ll = lca(nd[x], nd[u]);
      if (ll == nd[x])
      {
        sta[top++] = u;
        return;
      }
      while (top > 1 && dfn[nd[y = sta[top - 2]]] > dfn[ll])
      {
        e[y].emplace_back(x, dis[nd[x]] - dis[nd[y]]);
        x = y;
        top--;
      }
      top--;
      if (!top || ll != nd[sta[top - 1]])
      {
        int id     = m;
        sta[top++] = id;
        *buf_top++ = ll, ++m;
        e[id].clear();
      }
      e[sta[top - 1]].emplace_back(x, dis[nd[x]] - dis[nd[sta[top - 1]]]);
      sta[top++] = u;
    };

    for (int i = 0; i < (int)a.size(); ++i)
    {
      add(i);
    }
    while (top > 1)
    {
      int x = sta[--top];
      int y = sta[top - 1];
      e[y].emplace_back(x, dis[nd[x]] - dis[nd[y]]);
    }
    int rt = sta[0];

    std::function<void(int)> dfs = [&](int u) {
      *(buf_top++) = u;
      for (auto p : e[u])
      {
        fa[p.first] = u;
        dfs(p.first);
      }
    };

    fa = allocate(m);
    id = buf_top;
    dfs(rt);

    f       = allocate(m);
    g       = allocate(m);
    int *fc = allocate(m);
    for (int i = m - 1; i >= 0; --i)
    {
      int u = id[i];
      f[u]  = u < n ? 0 : -INF;
      fc[u] = -INF;
      for (auto p : e[u])
      {
        int v = p.first, w = p.second;
        if (f[v] + w > f[u])
        {
          fc[u] = f[u];
          f[u]  = f[v] + w;
        }
        else if (f[v] + w > fc[u])
        {
          fc[u] = f[v] + w;
        }
      }
    }

    int *fw = allocate(m);
    g[rt]   = -INF;
    for (int i = 0; i < m; ++i)
    {
      int u = id[i];
      for (auto p : e[u])
      {
        int v = p.first, w = p.second;
        if (f[v] + w == f[u])
          g[v] = std::max(g[u] + fw[u], fc[u]);
        else
          g[v] = std::max(g[u] + fw[u], f[u]);
        fw[v] = w;
      }
    }
    buf_top -= m + m;
  }

  vtree_t &operator=(const vtree_t &a)
  {
    if (this != &a)
    {
      n = a.n, m = a.m;
      nd = a.nd, fa = a.fa, f = a.f, g = a.g, id = a.id;
    }
    return *this;
  }

  int max_dist(int u)
  {
    auto cmp = [&](int x, int y) { return dfn[nd[x]] < dfn[y]; };
    int  p   = static_cast<int>(std::lower_bound(id, id + m, u, cmp) - id);
    int  v   = 0;
    if (p < m)
      v = std::max(v, lca(nd[id[p]], u), cmp_dep);
    if (p - 1 >= 0)
      v = std::max(v, lca(nd[id[p - 1]], u), cmp_dep);
    int q = static_cast<int>(std::lower_bound(id, id + m, v, cmp) - id);
    return dis[u] - dis[v] +
           std::max(f[id[q]] + dis[nd[id[q]]] - dis[v],
                    q ? g[id[q]] + dis[v] - dis[nd[fa[id[q]]]] : -INF);
  }
};

vtree_t merge(const vtree_t &a, const vtree_t &b)
{
  std::vector<int> v(a.n + b.n);
  std::merge(a.nd, a.nd + a.n, b.nd, b.nd + b.n, v.begin(), [&](int x, int y) {
    return dfn[x] < dfn[y];
  });
  return {v};
}

int lpow2(int n)
{
  int res = 1;
  while (res < n)
    res <<= 1;
  return res;
}

class sgt_t
{
  int     n, now;
  bool    ready[N << 2];
  vtree_t c[N << 2];

  void update(int u)
  {
    c[u]     = merge(c[u << 1], c[u << 1 | 1]);
    ready[u] = true;
  }

  void insert_impl(int u, int l, int r, int x)
  {
    if (r - l == 1)
    {
      c[u]     = vtree_t(std::vector<int>(1, x));
      ready[u] = true;
    }
    else
    {
      int mid = (l + r + 1) >> 1;
      if (now <= mid)
        insert_impl(u << 1, l, mid, x);
      else
      {
        insert_impl(u << 1 | 1, mid, r, x);
        if (now == r && (u & (u - 1)) && !ready[u - 1])
          update(u - 1);
      }
    }
  }

  void erase_impl(int u, int l, int r)
  {
    ready[u] = false;
    if (r - l == 1) {}
    else
    {
      int mid = (l + r + 1) >> 1;
      if (now <= mid)
        erase_impl(u << 1, l, mid);
      else
        erase_impl(u << 1 | 1, mid, r);
    }
  }

  int query_impl(int u, int l, int r, int ql, int qr, int x)
  {
    if (ql <= l && r <= qr && ready[u])
    {
      return c[u].max_dist(x);
    }
    else
    {
      int mid = (l + r + 1) >> 1;
      if (qr <= mid)
        return query_impl(u << 1, l, mid, ql, qr, x);
      else if (ql >= mid)
        return query_impl(u << 1 | 1, mid, r, ql, qr, x);
      else
        return std::max(query_impl(u << 1, l, mid, ql, qr, x),
                        query_impl(u << 1 | 1, mid, r, ql, qr, x));
    }
  }

public:
  void set(int _n)
  {
    n = _n;
  }

  void insert(int a)
  {
    ++now;
    insert_impl(1, 0, n, a);
  }

  void erase()
  {
    erase_impl(1, 0, n);
    --now;
  }

  int query(int l, int r, int a)
  {
    return query_impl(1, 0, n, l, r, a);
  }

  int len()
  {
    return now;
  }
};

sgt_t sgt;

int main()
{
  std::cin >> n >> m;
  for (int i = 1; i < n; ++i)
  {
    int u, v, w;
    std::cin >> u >> v >> w;
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
  }
  dfs(1);
  init_st();

  sgt.set(lpow2(m));
  int ans = 0;
  for (int i = 0; i < m; i++)
  {
    int op;
    std::cin >> op;
    if (op == 1)
    {
      int x;
      std::cin >> x;
      x = (x ^ abs(ans)) % n + 1;
      sgt.insert(x);
    }
    else if (op == 2)
    {
      sgt.erase();
    }
    else if (op == 3)
    {
      int l, r, x;
      std::cin >> l >> r >> x;
      l = (l ^ abs(ans)) % sgt.len() + 1;
      r = (r ^ abs(ans)) % sgt.len() + 1;
      if (l > r)
        std::swap(l, r);
      x = (x ^ abs(ans)) % n + 1;
      l--;

      ans = sgt.query(l, r, x);
      std::cout << ans << '\n';
    }
  }
}
