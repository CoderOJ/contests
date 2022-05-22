#include <bits/stdc++.h>

const int N = 500005;
const int B = 20;

std::vector<int> e[N];

int  n, m, x;
char c[N], s[N];

int  dep[N], fa[N][B];
void dfs_init(int u, int f)
{
  dep[u]   = dep[f] + 1;
  fa[u][0] = f;
  for (int i = 0; i + 1 < B; i++)
    fa[u][i + 1] = fa[fa[u][i]][i];
  for (int v : e[u])
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

void brute() 
{
  for (int i = 0; i < m; i++)
  {
    int opt, u, v;
    scanf("%d%d%d%s", &opt, &u, &v, s);
    if (opt == 1)
    {
      int l = lca(u, v);
      for (int p = u, i = 0; p != l; p = fa[p][0], i++)
        c[p] = s[i];
      for (int p = v, i = x - 1; p != l; p = fa[p][0], i--)
        c[p] = s[i];
    }
    else
    {
      static char bs[N];

      int l = lca(u, v);
      int dis = dep[u] + dep[v] - dep[l] * 2;
      for (int p = u, i = 0; p != l; p = fa[p][0], i++)
        bs[i] = c[p];
      for (int p = v, i = dis - 1; p != l; p = fa[p][0], i--)
        bs[i] = c[p];

      int ans = 0;
      for (int i = 0; i + x <= dis; i++)
      {
        char tmp = bs[i + x];
        bs[i + x] = '\0';
        if (strcmp(bs + i, s) == 0)
          ans += 1;
        bs[i + x] = tmp;
      }

      printf("%d\n", ans);
    }
  }
}

void puts_dis()
{
  for (int i = 0; i < m; i++)
  {
    int opt, u, v;
    scanf("%d%d%d%s", &opt, &u, &v, s);
    if (opt == 1)
    {
    }
    else
    {
      int l = lca(u, v);
      int dis = dep[u] + dep[v] - dep[l] * 2;
      printf("%d\n", std::max(dis - x + 1, 0));
    }
  }
}

int main()
{
  scanf("%d%d%d", &n, &m, &x);
  for (int i = 2; i <= n; i++)
  {
    int f;
    scanf("%d", &f);
    e[f].push_back(i);
  }
  dfs_init(1, 0);
  scanf("%s", c + 2);

  if (n <= 250 && m <= 250)
    brute();
  else
    puts_dis();

  return 0;
}
