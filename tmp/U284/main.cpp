#include <bits/stdc++.h>

#ifdef CM_DEBUG
const int N = 305;
#else
const int N = 300005;
#endif

const int B = 20;
int fa[N][B], w[N][B], dep[N], n;

int get_chain_max(int u, int d)
{
  if (d <= 0) return 0;
  int res = 0;
  for (int i = B - 1; i >= 0; i--)
    if (d & (1 << i))
    {
      res = std::max(res, w[u][i]);
      u = fa[u][i];
    }
  return res;
}

struct query_t
{
  int s, t;
  int chain_max;
  int64_t ans;
};

query_t qs[N];
std::vector<query_t *> qp;
int q;

struct node_t
{
  node_t *f = nullptr, *s[2] = {nullptr, nullptr};
  int min_dep = 0x3f3f3f3f, min_dep_assign = -1;
  int64_t ans = 0, ans_add = 0;
  
  bool is_root() const { return f == nullptr || (f->s[0] != this && f->s[1] != this); }
  bool get_son() const { return f->s[1] == this; }
  void push_min_assign(int val)
  {
    min_dep = val;
    min_dep_assign = val;
  }
  void push_ans_add(int64_t val)
  {
    ans += val;
    ans_add += val;
  }
  void push_down()
  {
    if (min_dep_assign != -1)
    {
      if (s[0] != nullptr) s[0]->push_min_assign(min_dep_assign);
      if (s[1] != nullptr) s[1]->push_min_assign(min_dep_assign);
      min_dep_assign = -1;
    }
    if (ans_add != 0)
    {
      if (s[0] != nullptr) s[0]->push_ans_add(ans_add);
      if (s[1] != nullptr) s[1]->push_ans_add(ans_add);
      ans_add = 0;
    }
  }
  void push()
  {
    if (!is_root()) f->push();
    push_down();
  }
  void rotate()
  {
    node_t *uu = this, *ff = f, *aa = ff->f; bool ss = get_son();
    if (!ff->is_root()) aa->s[ff->get_son()] = uu;
    ff->f = uu; ff->s[ss] = uu->s[!ss];
    uu->f = aa; uu->s[!ss] = ff;
    if (ff->s[ss] != nullptr) ff->s[ss]->f = ff;
  }
  void splay()
  {
    push();
    while (!is_root())
    {
      if (f->is_root()) { rotate(); break; }
      else
      {
        (f->get_son() == get_son() ? f : this)->rotate();
        rotate();
      }
    }
  }
  void access()
  {
    node_t *uu = this, *ss = nullptr;
    while (uu != nullptr)
    {
      uu->splay();
      uu->s[1] = ss;
      ss = uu;
      uu = uu->f;
    }
  }
};

node_t p[N];

void modify(node_t *p, int dep, int w)
{
  node_t *uu = p, *ss = nullptr;
  while (uu != nullptr)
  {
    uu->splay();
    uu->s[1] = nullptr;
    if (uu->min_dep > dep)
    {
      int64_t ans_det = 1ll * (dep - uu->min_dep) * w;
      uu->push_ans_add(ans_det);
      uu->push_min_assign(dep);
      uu->push_down();
      uu->s[1] = ss;
      ss = uu;
      uu = uu->f;
    }
    else
    {
      break;
    }
  }
}

int main()
{
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &w[i][0]);
  for (int i = 2; i <= n; i++) scanf("%d", &fa[i][0]);
  for (int i = 1; i <= n; i++)
  {
    dep[i] = dep[fa[i][0]] + 1;
    for (int b = 0; b + 1 < B; b++)
    {
      fa[i][b + 1] = fa[fa[i][b]][b];
      w[i][b + 1] = std::max(w[i][b], w[fa[i][b]][b]);
    }
  }

  scanf("%d", &q);
  for (int i = 0; i < q; i++)
  {
    scanf("%d%d", &qs[i].s, &qs[i].t);
    qs[i].chain_max = get_chain_max(fa[qs[i].t][0], dep[qs[i].t] - dep[qs[i].s] - 1);
    qp.push_back(&qs[i]);
  }
  std::sort(qp.begin(), qp.end(), [](query_t *x, query_t *y) {
    return x->chain_max > y->chain_max;
  });

  for (int i = 2; i <= n; i++) p[i].f = &p[fa[i][0]];
  std::vector<std::pair<int, int>> us;
  for (int u = 2; u <= n; u++) us.emplace_back(w[u][0], u);
  std::sort(us.begin(), us.end(), std::greater<std::pair<int, int>>());
  auto qp_it = qp.begin();
  for (const auto &[w, u] : us)
  {
    while (qp_it != qp.end() && (*qp_it)->chain_max >= w)
    {
      int s = (*qp_it)->s;
      p[s].splay();
      (*qp_it)->ans -= (p[s].ans - 1ll * p[s].min_dep * (*qp_it)->chain_max);
      qp_it++;
    }
    modify(&p[fa[u][0]], dep[u], w);
  }
  while (qp_it != qp.end())
  {
    int s = (*qp_it)->s;
    p[s].splay();
    (*qp_it)->ans -= (p[s].ans - 1ll * p[s].min_dep * (*qp_it)->chain_max);
    qp_it++;
  }
  for (auto &q : qp)
  {
    int s = q->s;
    p[s].splay();
    q->ans += p[s].ans;
    q->ans -= 1ll * q->chain_max * dep[q->s];
    q->ans += dep[q->t] - dep[q->s];
  }

  for (int i = 0; i < q; i++)
    printf("%" SCNi64 "\n", qs[i].ans);
  
  return 0;
}
