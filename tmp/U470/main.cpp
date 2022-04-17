#include <bits/stdc++.h>

const int N = 100005;
const int B = 18;

struct info_t
{
  int min = 0;
  int min_cnt = 1;

  info_t() = default;
  info_t(int min, int min_cnt) : min(min), min_cnt(min_cnt) {}
  info_t(const info_t &lhs, const info_t &rhs) : 
    min(std::min(lhs.min, rhs.min)),
    min_cnt((lhs.min == min ? lhs.min_cnt : 0) + (rhs.min == min ? rhs.min_cnt : 0)) {}

  info_t add(int det) const 
  {
    return {min + det, min_cnt};
  }
};

struct lct_t
{
  struct node_t
  {
    node_t *f = nullptr, *s[2] = {nullptr, nullptr};
    info_t val, sum;
    int add = 0;
    bool rev = false;

    void push_up()
    {
      sum = val;
      if (s[0]) sum = info_t(s[0]->sum, sum);
      if (s[1]) sum = info_t(sum, s[1]->sum);
    }

    void push_add(int det)
    {
      val = val.add(det);
      sum = sum.add(det);
      add += det;
    }

    void push_reverse()
    {
      std::swap(s[0], s[1]);
      rev = !rev;
    }

    void push_down()
    {
      if (add != 0)
      {
        if (s[0]) s[0]->push_add(add);
        if (s[1]) s[1]->push_add(add);
        add = 0;
      }
      if (rev)
      {
        if (s[0]) s[0]->push_reverse();
        if (s[1]) s[1]->push_reverse();
        rev = false;
      }
    }

    void push()
    {
      if (!is_root())
        f->push();
      push_down();
    }

    bool is_root() const
    {
      return f == nullptr || (f->s[0] != this && f->s[1] != this);
    }

    bool get_son() const
    {
      return f->s[1] == this;
    }

    void rotate()
    {
      node_t *uu=this, *ff = f, *aa = ff->f;
      bool ss = get_son();
      if (!ff->is_root()) aa->s[ff->get_son()] = uu;
      ff->f = uu; ff->s[ss] = uu->s[!ss];
      uu->f = aa; uu->s[!ss] = ff;
      if (ff->s[ss]) ff->s[ss]->f = ff;
      ff->push_up(); uu->push_up();
    }

    void splay()
    {
      push();
      while (!is_root())
      {
        if (f->is_root())
        {
          rotate();
          break;
        }
        else
        {
          if (get_son() == f->get_son())
            f->rotate();
          else
            rotate();
          rotate();
        }
      }
    }

    void access()
    {
      node_t *uu = this, *ss = nullptr;
      while (uu)
      {
        uu->splay();
        uu->s[1] = ss;
        uu->push_up();
        ss = uu;
        uu = uu->f;
      }
    }

    void make_root()
    {
      access();
      splay();
      push_reverse();
    }
  };

  node_t p[N];

  void split(int u, int v)
  {
    p[u].make_root();
    p[v].access();
    p[v].splay();
  }
};

lct_t t;

int zero_cnt;
void path_add(int u, int v, int d)
{
  // printf("path_add: (%d -> %d) += %d\n", u, v, d);
  t.split(u, v);
  // printf("t.p[v] = [%d %d]\n", t.p[v].sum.min, t.p[v].sum.min_cnt);
  zero_cnt -= t.p[v].sum.min == 0 ? t.p[v].sum.min_cnt : 0;
  t.p[v].push_add(d);
  zero_cnt += t.p[v].sum.min == 0 ? t.p[v].sum.min_cnt : 0;
  // printf("zero_cnt = %d\n", zero_cnt);
}

std::vector<int> e[N];
std::vector<std::pair<int, int>> pp[N];
int pu[N], pv[N];
int n, m;

int dep[N], fa[N][B];
int size[N], wson[N];
void dfs_init(int u, int f)
{
  dep[u] = dep[f] + 1;
  fa[u][0] = f;
  for (int i = 0; i + 1 < B; i++)
    fa[u][i + 1] = fa[fa[u][i]][i];
  size[u] = 1;
  for (int v: e[u]) if (v != f)
  {
    t.p[v].f = &t.p[u];
    dfs_init(v, u);
    size[u] += size[v];
    if (size[v] > size[wson[u]])
      wson[u] = v;
  }
}

int lca(int u, int v)
{
  if (dep[u] < dep[v]) std::swap(u, v);
  int d = dep[u] - dep[v];
  for (int i = 0; i < B; i++) if (d & (1 << i)) u = fa[u][i];
  for (int i = B - 1; i >= 0; i--)
    if (fa[u][i] != fa[v][i])
      u = fa[u][i], v = fa[v][i];
  return u == v ? u : fa[u][0];
}

void dfs_apply(int u, int f, int fac)
{
  // printf("dfs_apply %d: fac = %d\n", u, fac);
  if (fac == -1)
    for (const auto &[pi, pd] : pp[u])
      path_add(pu[pi], pv[pi], -pd);
  for (int v : e[u]) if (v != f) dfs_apply(v, u, fac);
  if (fac == 1)
    for (const auto &[pi, pd] : pp[u])
      path_add(pu[pi], pv[pi], pd);
}

int64_t ans = 0;

void dfs_solve(int u, int f)
{
  // printf("dfs_solve: %d\n", u);
  for (int v : e[u]) if (v != f && v != wson[u])
  {
    dfs_solve(v, u);
    dfs_apply(v, u, -1);
  }
  if (wson[u]) dfs_solve(wson[u], u);
  for (int v : e[u]) if (v != f && v != wson[u])
    dfs_apply(v, u, 1);
  for (const auto &[pi, pd] : pp[u])
    path_add(pu[pi], pv[pi], pd);
  ans += std::max(n - zero_cnt - 1, 0);

  // printf("ans(%d) = %d\n", u, n - zero_cnt - 1);
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    e[u].push_back(v);
    e[v].push_back(u);
  }
  dfs_init(1, 0);
  for (int i = 0; i < m; i++)
  {
    scanf("%d%d", &pu[i], &pv[i]);
    int l = lca(pu[i], pv[i]);
    pp[pu[i]].emplace_back(i, 1);
    pp[pv[i]].emplace_back(i, 1);
    pp[fa[l][0]].emplace_back(i, -2);
  }

  zero_cnt = n;
  dfs_solve(1, 0);
  printf("%" SCNi64 "\n", ans / 2);

  return 0;
}
