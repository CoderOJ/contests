#include <bits/stdc++.h>

const int N = 100005;
const int B = 20;
std::vector<int> e[N];
int n, m;

int dep[N], fa[N][B];
void dfs_init(int u, int f)
{
  dep[u] = dep[f] + 1; fa[u][0] = f;
  for (int i = 0; i + 1 < B; i++) fa[u][i + 1] = fa[fa[u][i]][i];
  for (int v : e[u]) if (v != f)
    if (dep[v] == 0) dfs_init(v, u);
}
int up(int u, int d)
{
  for (int i = 0; i < B; i++)
    if (d & (1 << i))
      u = fa[u][i];
  return u;
}

int cover[N], cnt[N];
void dfs_calc_cover(int u)
{
  for (int v : e[u]) if (dep[v] == dep[u] + 1)
    dfs_calc_cover(v), cover[u] += cover[v];
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++)
  {
    int u, v; scanf("%d%d", &u, &v);
    e[u].push_back(v); e[v].push_back(u);
  }
  dfs_init(1, 0);

  for (int u = 1; u <= n; u++) for (int v : e[u])
    if (dep[u] >= dep[v] + 2)
      cover[u]++, cover[v]--;
  dfs_calc_cover(1);

  std::vector<int> ans;
  for (int u = 2; u <= n; u++)
  {
    int e_cnt = m - (int)(e[u].size());
    if (e_cnt == n - 2)
    {
      for (int v : e[u]) if (dep[v] == dep[u] + 1) cnt[v] = cover[v];      
      for (int v : e[u]) if (dep[v] > dep[u] + 1) cnt[up(v, dep[v] - dep[u] - 1)]--;
      bool valid = true;
      for (int v : e[u]) if (dep[v] == dep[u] + 1) valid &= (cnt[v] == 1);
      if (valid) ans.push_back(u);
    }
  }

  memset(dep, 0, sizeof(dep)); memset(cover, 0, sizeof(cover));
  dfs_init(2, 0);
  for (int u = 1; u <= n; u++) for (int v : e[u])
    if (dep[u] >= dep[v] + 2)
      cover[u]++, cover[v]--;
  dfs_calc_cover(2);
  for (int u = 1; u <= 1; u++)
  {
    int e_cnt = m - (int)(e[u].size());
    if (e_cnt == n - 2)
    {
      for (int v : e[u]) if (dep[v] == dep[u] + 1) cnt[v] = cover[v];      
      for (int v : e[u]) if (dep[v] > dep[u] + 1) cnt[up(v, dep[v] - dep[u] - 1)]--;
      bool valid = true;
      for (int v : e[u]) if (dep[v] == dep[u] + 1) valid &= (cnt[v] == 1);
      if (valid) ans.push_back(u);
    }
  }

  std::sort(ans.begin(), ans.end());
  printf("%zu\n", ans.size());
  for (int x : ans) printf("%d ", x);
  puts("");

  return 0;
}
