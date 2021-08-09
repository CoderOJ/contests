#include <bits/stdc++.h>
#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/util.hpp"

constexpr int N = 405;
int MOD;

int power(int a, int b)
{
  int r = 1;
  for (; b; b >>= 1)
  {
    if (b & 1) 
      r = 1ll * r * a % MOD;
    a = 1ll * a * a % MOD;
  }
  return r;
}

int inv(int a)
{
  return power(a, MOD - 2);
}

struct matrix_t
{
  int a[N][N];
  matrix_t() { memset(a, 0, sizeof(a)); }
  int det(int n)
  {
    int ans = 1;
    for (int i = 0; i < n; i++)
    {
      int non_zero_id = -1;
      for (int j = i; j < n; j++)
        if (a[j][i] != 0)
        {
          non_zero_id = j;
          break;
        }
      if (non_zero_id == -1) 
        return 0;
      if (non_zero_id != i)
      {
        ans = -ans;
        for (int j = i; j < n; j++)
          std::swap(a[i][j], a[non_zero_id][j]);
      }
      for (int j = i + 1; j < n; j++)
      {
        int factor = 1ll * inv(a[i][i]) * a[j][i] % MOD;
        for (int k = i; k < n; k++)
          a[j][k] = (a[j][k] - 1ll * a[i][k] * factor) % MOD;
      }
      ans = 1ll * ans * a[i][i] % MOD;
    }
    return (ans + MOD) % MOD;
  }
};

constexpr int M = 105 * 105;

struct dsu_t
{
  int p[M];
  int id[M];

  dsu_t()
  {
    for (int i = 0; i < M; i++)
      p[i] = i;
  }
  int get(int u)
  {
    return u == p[u] ? u : p[u] = get(p[u]);
  }
};

using edge_t = std::pair<int,int>;

int calc(const std::vector<edge_t> &must, const std::vector<edge_t> alter, int n)
{
  dsu_t st;
  for (const auto& [u,v] : must)
  {
    int pu = st.get(u);
    int pv = st.get(v);
    if (pu == pv) return 0;
    st.p[pu] = pv;
  }
  int id_cnt = 0;
  for (int i = 0; i < n; i++) 
    if (st.p[i] == i)
      st.id[i] = id_cnt++;
  if (id_cnt - 1> (int)alter.size())
    return 0;
  matrix_t mt;
  for (const auto& [u,v] : alter)
  {
    int pu = st.id[st.get(u)], pv = st.id[st.get(v)];
    see(pu, pv);
    mt.a[pu][pu]++;
    mt.a[pv][pv]++;
    mt.a[pu][pv]--;
    mt.a[pv][pu]--;
  }
  see(id_cnt - 1);
  return mt.det(id_cnt - 1);
}

char a[105][105];
int id[105][105];
int n, m;

int main()
{
  n = sc.n(); m = sc.n(); MOD = sc.n();
  for (int i = 0; i < n; i++)
    sc.next(a[i]);

  int cnt[2] = {0, 0};
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++)
      id[i][j] = cnt[(i + j) % 2]++;
  int ans = 0;
  {
    std::vector<edge_t> must, alter;
    for (int i = 0; i < n; i++) 
      for (int j = 0; j < m; j++)
      {
        int u = (i + j) % 2 == 0 ? id[i][j] : id[i][j + 1];
        int v = (i + j) % 2 == 0 ? id[i + 1][j + 1] : id[i + 1][j];
        if (a[i][j] == '*') alter.push_back({u, v});
        else if (a[i][j] == ((i + j) % 2 == 0 ? '\\' : '/')) must.push_back({u, v});
      }
    see(must);
    see(alter);
    ans += calc(must, alter, cnt[0]);
    see(ans);
  }
  {
    std::vector<edge_t> must, alter;
    for (int i = 0; i < n; i++) 
      for (int j = 0; j < m; j++)
      {
        int u = (i + j) % 2 == 0 ? id[i][j + 1] : id[i][j];
        int v = (i + j) % 2 == 0 ? id[i + 1][j] : id[i + 1][j + 1];
        if (a[i][j] == '*') alter.push_back({u, v});
        else if (a[i][j] == ((i + j) % 2 == 0 ? '/' : '\\')) must.push_back({u, v});
      }
    see(must);
    see(alter);
    ans += calc(must, alter, cnt[1]);
    see(ans);
  }
  printf("%d\n", ans % MOD);
  return 0;
}
