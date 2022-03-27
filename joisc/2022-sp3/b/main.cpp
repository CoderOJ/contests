#include <bits/stdc++.h>

const int N = 200005;
const int B = 45;

std::vector<int> e[N];
int n, q, mod, a[N];

int fa[N], dep[N], fac[N][B];
void dfs_init(int u, int f)
{
  fa[u] = f; dep[u] = dep[f] + 1;
  for (int v : e[u]) if (v != f) dfs_init(v, u);
}

int main()
{
  scanf("%d%d", &n, &mod);  
  for (int i = 0; i < n - 1; i++)
  { int u, v; scanf("%d%d", &u, &v); e[u].push_back(v); e[v].push_back(u); }
  for (int i = 1; i <= n; i++) for (int j = 0; j < B; j++) fac[i][j] = 1;
  dfs_init(1, 0);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  scanf("%d", &q);
  for (int i = 0; i < q; i++)
  {
    int type; scanf("%d", &type);
    if (type == 1)
    {
      int u, d, w; scanf("%d%d%d", &u, &d, &w);
      // printf("modify: %d %d %d\n", u, d, w);
      int p = u;
      for (int i = dep[u] + d; i >= std::max(1, dep[u] - d); i--)
      {
        int vpu = dep[u] - (dep[u] + d - i) / 2;
        while (p != 1 && dep[p] > vpu) { p = fa[p]; }
        // printf("vpu = %d, i = %d, p = %d, %d\n", vpu, i, p, i - dep[p]);
        fac[p][i - dep[p]] = 1ll * fac[p][i - dep[p]] * w % mod;
      }
    }
    else
    {
      int u; scanf("%d", &u);
      int ans = a[u];
      for (int i = 0, p = u; i < B && p > 0; i++, p = fa[p])
        ans = 1ll * ans * fac[p][i] % mod;
      printf("%d\n", ans);
    }
  }
  return 0;
}
