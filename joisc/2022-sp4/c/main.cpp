#include <bits/stdc++.h>

const int N = 505;
const int INF = 2e9;

struct edge_t
{
  int u, v, w, l, r, id;
};

std::vector<edge_t> es;
int n, m, q;

std::vector<std::pair<int, int>> e[N];
std::vector<int> path;
bool dfs(int u, int f, int t)
{
  if (u == t) return true;
  for (const auto &[v, eid] : e[u]) if (v != f)
    if (dfs(v, u, t)) { path.push_back(eid); return true; }
  return false;
}

struct query_t
{
  int p; long long ans;
};
std::vector<query_t> qs;

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) { 
    int u, v, w; scanf("%d%d%d", &u, &v, &w); es.push_back({u, v, w, -INF, INF, -1}); }
  std::sort(es.begin(), es.end(), [](edge_t x, edge_t y) { return x.w < y.w; });
  for (int i = 0; i < m; i++) es[i].id = i;
  for (auto &[u, v, w, l, r, id] : es)
  {
    path.clear(); bool vis = dfs(u, u, v);
    e[u].push_back({v, id}); e[v].push_back({u, id});
    if (vis)
    {
      int min_id = path[0]; for (int id : path) if (es[id].w < es[min_id].w) min_id = id;
      auto &[mu, mv, mw, ml, mr, _] = es[min_id];
      e[mu].erase(std::find(e[mu].begin(), e[mu].end(), std::make_pair(mv, min_id)));
      e[mv].erase(std::find(e[mv].begin(), e[mv].end(), std::make_pair(mu, min_id)));
      mr = mw + (w - mw) / 2 + 1; l = mr;
    }
  }

  scanf("%d", &q);
  for (int i = 0; i < q; i++) { int p; scanf("%d", &p); qs.push_back({p, 0}); }

  std::vector<query_t *> qp; for (int i = 0; i < q; i++) qp.push_back(&qs[i]);
  std::vector<edge_t>  ea = es;
  std::vector<edge_t>  eb = es;
  {
    std::sort(qp.begin(), qp.end(), [](query_t *x, query_t *y) { return x->p < y->p; });
    std::sort(ea.begin(), ea.end(), [](edge_t x, edge_t y) { return x.l < y.l; });
    std::sort(eb.begin(), eb.end(), [](edge_t x, edge_t y) { return x.w < y.w; });
    auto ea_it = ea.begin(), eb_it = eb.begin();
    long long cnt = 0, sum = 0;
    for (auto q : qp)
    {
      while (ea_it != ea.end() && ea_it->l <= q->p) { cnt += 1; sum += ea_it->w; ea_it++; }
      while (eb_it != eb.end() && eb_it->w <= q->p) { cnt -= 1; sum -= eb_it->w; eb_it++; }
      q->ans += sum - q->p * cnt;
    }
  }
  {
    std::sort(qp.begin(), qp.end(), [](query_t *x, query_t *y) { return x->p > y->p; });
    std::sort(ea.begin(), ea.end(), [](edge_t x, edge_t y) { return x.r > y.r; });
    std::sort(eb.begin(), eb.end(), [](edge_t x, edge_t y) { return x.w > y.w; });
    auto ea_it = ea.begin(), eb_it = eb.begin();
    long long cnt = 0, sum = 0;
    for (auto q : qp)
    {
      while (ea_it != ea.end() && q->p < ea_it->r) { cnt += 1; sum += ea_it->w; ea_it++; }
      while (eb_it != eb.end() && q->p < eb_it->w) { cnt -= 1; sum -= eb_it->w; eb_it++; }
      q->ans += q->p * cnt - sum;
    }
  }

  for (const auto &q : qs)
    printf("%lld\n", q.ans);

  return 0;
}
