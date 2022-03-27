#include <bits/stdc++.h>

#define ses(x) std::cout << #x << " = " << x << " "
#define see(x) std::cout << #x << " = " << x << std::endl

const int N = 120'005;
const int B = 20;

std::vector<int> t[N];
std::vector<int> e[N * B];

int n, m;
int u[N], v[N];

int cur_u;
int ru[N][B];
int fa[N][B];
int dep[N];

void dfs_init(int u, int f)
{
  dep[u] = dep[f] + 1;
  fa[u][0] = f;
  // ru[u][0] = cur_u++;
  for (int i = 0; i + 1 < B; i++)
  {
    fa[u][i + 1] = fa[fa[u][i]][i];
    // ru[u][i + 1] = cur_u++;
    // e[ru[u][i + 1]].push_back(ru[u][i]);
    // e[ru[u][i + 1]].push_back(ru[fa[u][i]][i]);
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

bool on_path(int u, int v, int r)
{
  int luv = lca(u, v);
  int lur = lca(u, r);
  int lvr = lca(v, r);
  return (lur == r || lvr == r) && (dep[r] >= dep[luv]);
}

bool vis[N], instack[N];
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
    for (int j = 0; j < m; j++)
      if (i != j)
      {
        if (on_path(u[i], v[i], u[j]) || on_path(u[j], v[j], v[i]))
        {
          // ses("add edge"); ses(i); see(j);
          e[i].push_back(j);
        }
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
