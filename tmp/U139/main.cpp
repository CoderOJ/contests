#include <bits/stdc++.h>

const int N = 100005;
std::vector<int> e[N];
int n;

int min_dep[N];
void dfs_calc_min_dep(int u, int f)
{
  if (u != 1 && e[u].size() == 1) min_dep[u] = 1;
  else min_dep[u] = 0x3f3f3f3f;
  for (int v : e[u]) if (v != f)
  {
    dfs_calc_min_dep(v, u);
    min_dep[u] = std::min(min_dep[u], min_dep[v] + 1);
  }
}

int dfs_assign(int u, int f, int d)
{
  int ans = 0;
  if (min_dep[u] == d)
  {
    ans += 1;
    d -= 1;
  }
  for (int v : e[u]) if (v != f)
    ans += dfs_assign(v, u, d);
  return ans;
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    e[u].push_back(v);
    e[v].push_back(u);
  }
  dfs_calc_min_dep(1, 0);
  int ans = dfs_assign(1, 0, min_dep[1]);
  printf("%d\n", ans);
  return 0;
}
