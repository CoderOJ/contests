#include <bits/stdc++.h>

#define ses(x) std::cout << #x << " = " << x << " "
#define see(x) std::cout << #x << " = " << x << std::endl

const int N = 120'005;
const int B = 18;

std::vector<int> t[N];
std::vector<int> e[N * (B + 2) * 2];

int n, m;
int u[N], v[N];

int cur_u;
int ru[N][B], su[N][B];
int fa[N][B];
int dep[N];

void dfs_init(int u, int f)
{
  dep[u] = dep[f] + 1;
  fa[u][0] = f;
  ru[u][0] = cur_u++;
  su[u][0] = cur_u++;
  for (int i = 0; i + 1 < B; i++)
  {
    fa[u][i + 1] = fa[fa[u][i]][i];
    ru[u][i + 1] = cur_u++;
    su[u][i + 1] = cur_u++;
    e[ru[u][i]].push_back(ru[u][i + 1]);
    e[su[u][i + 1]].push_back(su[u][i]);
    if (fa[u][i] != 0)
    {
      e[ru[fa[u][i]][i]].push_back(ru[u][i + 1]);
      e[su[u][i + 1]].push_back(su[fa[u][i]][i]);
    }
  }
  for (int v : t[u]) if (v != f) dfs_init(v, u);
}

int lca(int u, int v)
{
  if (dep[u] < dep[v]) std::swap(u, v);
  for (int d = dep[u] - dep[v], i = 0; i < B; i++)
    if (d & (1 << i))
      u = fa[u][i];
  for (int i = B - 1; i >= 0; i--)
    if (fa[u][i] != fa[v][i])
      u = fa[u][i], v = fa[v][i];
  return u == v ? u : fa[u][0];
}

int up(int u, int d)
{
  for (int i = 0; i < B; i++)
    if (d & (1 << i))
      u = fa[u][i];
  return u;
}

int get_fa(int r, int u)
{
  if (lca(r, u) == u)
    return up(r, dep[r] - dep[u] - 1);
  else
    return fa[u][0];
}

bool vis[N * (B + 2) * 2], instack[N * (B + 2) * 2];
bool dfs_find_cycle(int u)
{
  vis[u] = true; instack[u] = true;

  bool res = false;
  for (int v: e[u])
  {
    if (!vis[v])
      res |= dfs_find_cycle(v);
    else if (instack[v])
      return true;
  }

  instack[u] = false;

  return res;
}

void add_edge_ru(int u, int d, int v)
{
  int b = 31 - __builtin_clz(d);
  e[ ru[u][b] ].push_back(v);
  e[ ru[up(u, d - (1<<b))][b] ].push_back(v);
}

void add_edge_ru_chain(int u, int v, int r)
{
  int l = lca(u, v);
  add_edge_ru(u, dep[u] - dep[l] + 1, r);
  add_edge_ru(v, dep[v] - dep[l] + 1, r);
}

void add_edge_su(int u, int d, int v)
{
  int b = 31 - __builtin_clz(d);
  e[v].push_back( su[u][b] );
  e[v].push_back( su[up(u, d - (1<<b))][b] );
}

void add_edge_su_chain(int u, int v, int r)
{
  int l = lca(u, v);
  add_edge_su(u, dep[u] - dep[l] + 1, r);
  add_edge_su(v, dep[v] - dep[l] + 1, r);
}

void rmain()
{
  scanf("%d", &n);
  for (int i = 1; i < n; i++)
  {
    int u, v; scanf("%d%d", &u, &v);
    t[u].push_back(v);
    t[v].push_back(u);
  }
  scanf("%d", &m);
  for (int i = 0; i < m; i++)
  {
    int u, v; scanf("%d%d", &u, &v);
    ::u[i] = u, ::v[i] = v;
  }

  cur_u = m;
  dfs_init(1, 0);
  
  for (int i = 0; i < m; i++)
  {
    int u = ::u[i], v = ::v[i];
    int fu = get_fa(v, u), fv = get_fa(u, v);

    add_edge_su_chain(fu, v, i);
    e[su[u][0]].push_back(i);

    e[i].push_back(ru[v][0]);
    add_edge_ru_chain(u, fv, i);
  }

  bool have_cycle = false;
  for (int i = 0; i < cur_u && !have_cycle; i ++)
    if (!vis[i])
      have_cycle |= dfs_find_cycle(i);

  puts(have_cycle ? "No" : "Yes");

  for (int i = 1; i <= n; i++)
    t[i].clear();
  for (int i = 0; i < cur_u; i++)
  {
    e[i].clear();
    vis[i] = false;
    instack[i] = false;
  }
}

int main()
{
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++)
    rmain();
  return 0;
}
