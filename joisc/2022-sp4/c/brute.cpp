#include <bits/stdc++.h>

struct edge_t
{
  int u, v, w, aw;
};

std::vector<edge_t> es;
int n, m, q;

struct dsu_t
{
  std::vector<int> p;
  dsu_t(int n) : p(n) { for (int i = 0; i < n; i++) p[i] = i; }
  int get(int u) { return u == p[u] ? u : p[u] = get(p[u]); }
  void join(int u, int v) { p[get(u)] = get(v); }
};

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) { 
    int u, v, w; scanf("%d%d%d", &u, &v, &w); es.push_back({u, v, w, 0}); }

  scanf("%d", &q);
  for (int i = 0; i < q; i++)
  {
    int w; scanf("%d", &w);
    for (auto &p : es) p.aw = std::abs(p.w - w);
    std::sort(es.begin(), es.end(), [](auto x, auto y) { return x.aw < y.aw; });
    long long ans = 0;
    dsu_t dsu(n + 1);
    for (const auto &p : es) 
      if (dsu.get(p.u) != dsu.get(p.v))
        dsu.join(p.u, p.v), ans += p.aw;
    printf("%lld\n", ans);
  }

  return 0;
}
