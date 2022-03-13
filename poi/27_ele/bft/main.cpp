#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 100'005;

struct dsu_t
{
  int p[N];
  int size[N];

  dsu_t()
  {
    for (int i = 0; i < N; i++)
    {
      p[i]    = i;
      size[i] = 1;
    }
  }

  int get(int u)
  {
    return u == p[u] ? u : p[u] = get(p[u]);
  }

  void merge(int u, int v)
  {
    u = get(u);
    v = get(v);
    if (u != v)
    {
      size[u] += size[v];
      p[v] = u;
    }
  }
};

dsu_t dw;
dsu_t da;

struct query_t
{
  int     thr;
  int64_t ans;
};

query_t qs[N * 2];

struct edge_t
{
  int u, v;
  int w, c;
};

int n, q;

int main()
{
  n = sc.next_int();
  q = sc.next_int();

  std::vector<edge_t> es(n - 1);
  for (int i = 0; i < n - 1; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    int w = sc.next_int();
    int c = sc.next_int();
    es[i] = {u, v, w, c};
  }

  std::sort(es.begin(), es.end(), [](auto x, auto y) { return x.w > y.w; });

  for (int i = 0; i < q; i++)
  {
    qs[i].thr = sc.next_int();
  }

  std::vector<query_t *> qss(q);
  for (int i = 0; i < q; i++)
    qss[i] = &qs[i];

  std::sort(
      qss.begin(), qss.end(), [](auto x, auto y) { return x->thr > y->thr; });

  int64_t ans  = 0;
  auto    e_it = es.begin();
  for (query_t *q : qss)
  {
    while (e_it != es.end() && e_it->w >= q->thr)
    {
      int u = e_it->u, v = e_it->v, c = e_it->c;
      int suw = dw.size[dw.get(u)], svw = dw.size[dw.get(v)];
      int sua = da.size[da.get(u)], sva = da.size[da.get(v)];
      ans += 1ll * sua * sva;
      if (c == 0)
        ans -= 1ll * suw * svw;
      da.merge(u, v);
      if (c == 0)
        dw.merge(u, v);
      e_it++;
    }
    q->ans = ans;
  }

  for (int i = 0; i < q; i++)
    std::cout << qs[i].ans << std::endl;

  return 0;
}
