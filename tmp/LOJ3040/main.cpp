#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 500005, 1005)
constexpr int B = 20;

std::vector<int> e[N];
std::vector<int> col_u[N];

int n, k;

int  fa[N][B], dep[N];
void dfs_init(int u, int f)
{
  dep[u]   = dep[f] + 1;
  fa[u][0] = f;
  for (int i = 0; i + 1 < B; i++)
    fa[u][i + 1] = fa[fa[u][i]][i];
  for (int v : e[u])
    if (v != f)
      dfs_init(v, u);
}

int lca(int u, int v)
{
  if (dep[u] < dep[v])
    std::swap(u, v);
  int d = dep[u] - dep[v];
  for (int i = 0; i < B; i++)
    if (d & (1 << i))
      u = fa[u][i];
  for (int i = B - 1; i >= 0; i--)
    if (fa[u][i] != fa[v][i])
      u = fa[u][i], v = fa[v][i];
  return u == v ? u : fa[u][0];
}

int p[N];
int get(int u)
{
  return p[u] == u ? u : p[u] = get(p[u]);
}

void join(int u, int t)
{
  u = get(u);
  t = get(t);
  if (dep[u] > dep[t])
  {
    p[u] = fa[u][0];
    join(u, t);
  }
}

int deg[N];

int main()
{
  n = sc.next_int();
  k = sc.next_int();
  for (int i = 0; i < n - 1; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    e[u].push_back(v);
    e[v].push_back(u);
  }
  dfs_init(1, 0);
  for (int i = 1; i <= n; i++)
  {
    int c = sc.next_int();
    col_u[c].push_back(i);
  }

  for (int i = 1; i <= n; i++)
    p[i] = i;
  for (int i = 1; i <= k; i++)
    for (int v : col_u[i])
    {
      int u = col_u[i][0];
      int l = lca(u, v);
      join(u, l);
      join(v, l);
    }

  for (int u = 1; u <= n; u++)
    for (int v : e[u])
      if (v > u)
      {
        int pu = get(u), pv = get(v);
        if (pu != pv)
          deg[pu]++, deg[pv]++;
      }

  int c = static_cast<int>(std::count(deg + 1, deg + n + 1, 1));
  see(std::vector(deg + 1, deg + n + 1));
  see(c);
  std::cout << (c == 1 ? 0 : (c + 1) / 2) << std::endl;

  return 0;
}
