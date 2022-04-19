#include <bits/stdc++.h>

const int N = 1000005;

struct node_t
{
  node_t *f = nullptr, *s[2] = {nullptr, nullptr};
  int64_t val = 0, add = 0;

  bool is_root() const
  {
    return f == nullptr || (f->s[0] != this && f->s[1] != this);
  }

  bool get_son() const
  {
    return f->s[1] == this;
  }

  void push_add(int64_t det)
  {
    val += det;
    add += det;
  }

  void push_down()
  {
    if (add != 0)
    {
      if (s[0]) s[0]->push_add(add);
      if (s[1]) s[1]->push_add(add);
      add = 0;
    }
  }

  void push()
  {
    if (!is_root())
      f->push();
    push_down();
  }

  void rotate()
  {
    node_t *uu = this, *ff = uu->f, *aa = ff->f;
    const bool ss = uu->get_son();
    if (!ff->is_root()) aa->s[ff->get_son()] = uu;
    ff->f = uu; ff->s[ss] = uu->s[!ss];
    uu->f = aa; uu->s[!ss] = ff;
    if (ff->s[ss]) ff->s[ss]->f = ff;
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

  node_t *find_root()
  {
    node_t *u = this;
    while (u->s[0])
      u = u->s[0];
    u->splay();
    return u;
  }

  void access(int);
};

std::vector<int> e[N];
node_t p[N];
int64_t ans;
int w[N], n, m;

void node_t::access(int det)
{
  auto calc = [](node_t *uu, node_t *vv) -> int64_t {
    if (vv == nullptr)
      return std::max<int64_t>(uu->val - 1, 0);
    else
      return std::min(std::max<int64_t>(uu->val - 1, 0), (uu->val - vv->val) * 2);
  };

  node_t *uu = this, *ss = nullptr;
  while (uu)
  {
    uu->splay();

    node_t *vv = uu->s[1];
    uu->s[1] = nullptr;

    if (vv) vv = vv->find_root();
    if (ss) ss = ss->find_root();
    if (ss) ans -= calc(uu, vv);

    uu->push_add(det);
    uu->push_down();

    if (vv && (uu->val - vv->val) * 2 < uu->val - 1)
      uu->s[1] = vv;
    if (ss && (uu->val - ss->val) * 2 < uu->val - 1)
      uu->s[1] = ss;

    if (ss) ans += calc(uu, uu->s[1]);

    ss = uu;
    uu = uu->f;
  }
}

void dfs_init(int u, int f)
{
  p[u].f = &p[f];
  p[u + n].f = &p[u];
  for (int v : e[u]) 
    if (v != f)
      dfs_init(v, u);
}

int64_t sum[N];
int64_t dp(int u, int f)
{
  sum[u] = w[u];
  int64_t max = w[u];
  int64_t res = 0;
  for (int v : e[u]) if (v != f)
  {
    res += dp(v, u);
    max = std::max(max, sum[v]);
    sum[u] += sum[v];
  }
  res += std::min(std::max(sum[u] - 1, 0l), (sum[u] - max) * 2);
  return res;
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%d", &w[i]);
  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    e[u].push_back(v);
    e[v].push_back(u);
  }

  dfs_init(1, 0);
  for (int i = 1; i <= n; i++)
    p[i + n].access(w[i]);

  printf("%" SCNi64 "\n", ans);
  for (int i = 0; i < m; i++)
  {
    int u, w;
    scanf("%d%d", &u, &w);
    p[u + n].access(w);
    printf("%" SCNi64 "\n", ans);
  }

  return 0;
}
