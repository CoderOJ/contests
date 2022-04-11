#include <bits/stdc++.h>

template <int N>
struct trace_dsu
{
  int  p[N];
  int  s[N];
  std::stack<std::pair<int, int>> trace;

  trace_dsu()
  {
    for (int i = 0; i < N; i++)
    {
      p[i] = i;
      s[i] = 1;
    }
  }

  void backtrace()
  {
    int k, v;
    std::tie(k, v) = trace.top();
    trace.pop();
    s[k] = v;
    std::tie(k, v) = trace.top();
    trace.pop();
    p[k] = v;
  }

  int get(int u)
  {
    return u == p[u] ? u : get(p[u]);
  }

  bool join(int u, int v)
  {
    u = get(u);
    v = get(v);
    if (u == v)
    {
      trace.emplace(N - 1, 0);
      trace.emplace(N - 1, 0);
      return false;
    }
    else
    {
      if (s[u] < s[v])
        std::swap(u, v);
      trace.emplace(v, p[v]);
      trace.emplace(u, s[u]);
      p[v] = u;
      s[u] = s[u] + s[v];
      return true;
    }
  }
};

const int N = 500005;
const int K = 50;

trace_dsu<N * 4> dsu;
int uu[N][K];

struct modify_t
{
  int l, r;
  int u, v, c;
  modify_t *last;
  bool success;

  void apply()
  {
    if (c != -1)
    {
      // printf("applying modification %d %d -> %d\n", u, v, c);
      int u0 = uu[u][c];
      int v0 = uu[v][c];
      dsu.join(u0, v0 + 1);
      dsu.join(v0, u0 + 1);
    }
  }

  void backtrace()
  {
    if (c != -1)
    {
      // printf("backtrace modification %d %d -> %d\n", u, v, c);
      dsu.backtrace();
      dsu.backtrace();
    }
  }
};

struct query_t
{
  modify_t *goal;

  void apply()
  {
    int u = goal->u, v = goal->v, c = goal->c;
    // printf("testing modification %d %d -> %d\n", u, v, c);
    int pu0 = dsu.get(uu[u][c]);
    int pv0 = dsu.get(uu[v][c]);
    // printf("pu0 = %d, pv0 = %d\n", pu0, pv0);
    if (pu0 == pv0)
    {
      goal->success = false;
      goal->c = goal->last ? goal->last->c : -1;
    }
    else 
    { 
      goal->success = true;
    }
  }
};

struct sgt_node_t
{
  std::vector<modify_t *> modifies; 
  std::vector<query_t> queries;
};

sgt_node_t p[N * 4];

void sgt_insert(int u, int l, int r, int ml, int mr, auto f)
{
  // printf("sgt_insert [%d] [%d, %d)\n", u, l, r);
  if (ml <= l && r <= mr)
  {
    f(p[u]);
  }
  else
  {
    int m = l + (r - l) / 2;
    if (ml < m)
      sgt_insert(u + 1, l, m, ml, mr, f);
    if (mr > m)
      sgt_insert(u + (m - l) * 2, m, r, ml, mr, f);
  }
}

void sgt_apply(int u, int l, int r)
{
  // printf("sgt_apply [%d] [%d, %d)\n", u, l, r);
  for (auto p : p[u].modifies)
    p->apply();

  if (r - l == 1)
  {
    for (auto q : p[u].queries)
      q.apply();
  }
  else
  {
    int m = l + (r - l) / 2;
    sgt_apply(u + 1, l, m);
    sgt_apply(u + (m - l) * 2, m, r);
  }

  for (auto p : p[u].modifies)
    p->backtrace();
}

modify_t modifies[N];
modify_t *last_modify[N];
int u[N], v[N], e[N], c[N];
int n, m, k, q, cur_u;

int main()
{
  scanf("%d%d%d%d", &n, &m, &k, &q);
  for (int i = 0; i < m; i++) 
    scanf("%d%d", &u[i], &v[i]);
  for (int i = 0; i < q; i++)
  {
    scanf("%d%d", &e[i], &c[i]);
    e[i]--, c[i]--;
  }

  memset(uu, -1, sizeof(uu));
  cur_u = 0;
  for (int i = 0; i < q; i++)
  {
    int u = ::u[e[i]], v = ::v[e[i]], c = ::c[i];
    if (uu[u][c] == -1) uu[u][c] = cur_u, cur_u += 2;
    if (uu[v][c] == -1) uu[v][c] = cur_u, cur_u += 2;
  }

  for (int i = 0; i < q; i++)
  {
    modifies[i].u = u[e[i]];    
    modifies[i].v = v[e[i]];    
    modifies[i].c = c[i];
    modifies[i].last = last_modify[e[i]];
    modifies[i].l = i * 2;
    modifies[i].r = -1;
    if (modifies[i].last)
      modifies[i].last->r = i * 2 - 1;
    last_modify[e[i]] = &modifies[i];
  }
  for (int i = 0; i < q; i++)
    if (modifies[i].r == -1)
      modifies[i].r = q * 2 - 1;

  for (int i = 0; i < q; i++)
  {
    auto &cur = modifies[i];
    // printf("add modify: [%d, %d) %d %d -> %d\n", cur.l, cur.r, cur.u, cur.v, cur.c);
    sgt_insert(0, -1, q * 2, cur.l, cur.r, [&](sgt_node_t &p) {
      p.modifies.push_back(&cur);
    });
    sgt_insert(0, -1, q * 2, cur.l - 1, cur.l, [&](sgt_node_t &p) {
      p.queries.push_back({&cur});
    });
  }

  sgt_apply(0, -1, q * 2);

  for (int i = 0; i < q; i++)
    puts(modifies[i].success ? "YES" : "NO");

  return 0;
}
