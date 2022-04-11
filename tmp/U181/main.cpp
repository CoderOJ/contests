#include <bits/stdc++.h>

const int MOD = 998244353;
const int N = 50;
std::vector<int> e[N];
int p[N][N];
int n, m;

bool vis[N];
void dfs(std::vector<int> &us, int u)
{
  vis[u] = true;
  us.push_back(u);
  for (int v : e[u]) if (!vis[v]) dfs(us, v);
}

int inv(int x)
{
  return x == 1 ? 1 : 1ll * inv(MOD % x) * (MOD - MOD / x) % MOD;
}

auto inv2 = []{
  std::array<int, N * N> a;
  a[0] = 1;
  a[1] = inv(2);
  for (int i = 2; i < N * N; i++)
    a[i] = 1ll * a[i - 1] * a[1] % MOD;
  return a;
}();

std::vector<int> solve(const std::vector<int> &us)
{
  static int a[1 << 20], b[1 << 20];
  int n = static_cast<int>(us.size());
  std::fill(a, a + (1 << n), 1);
  std::fill(b, b + (1 << n), 0);
  for (int u = 0; u < n; u++)
    for (int v = 0; v < n; v++)
    {
      int c = p[us[u]][us[v]];
      if (c != 0)
      {
        a[1 << u] = 1ll * a[1 << u] * c % MOD;
        a[1 << u | 1 << v] = 1ll * a[1 << u | 1 << v] * inv(c) % MOD;
      }
      else
      {
        b[1 << u]++;
        b[1 << u | 1 << v]--;
      }
    }
  for (int i = 0; i < n; i++)
    for (int j = 0; j < (1 << n); j++)
      if (j & (1 << i))
      {
        a[j] = 1ll * a[j] * a[j ^ (1 << i)] % MOD;
        b[j] += b[j ^ (1 << i)];
      }
  
  std::vector<int> res(n + 1, 0);
  for (int i = 0; i < (1 << n); i++)
    if (b[i] == 0)
    {
      int c = __builtin_popcount(i);
      res[c] = (res[c] + a[i]) % MOD;
    }
  return res;
}

std::vector<int> join(const std::vector<int> &lhs, const std::vector<int> &rhs)
{
  int ln = static_cast<int>(lhs.size()) - 1;
  int rn = static_cast<int>(rhs.size()) - 1;
  std::vector<int> res(ln + rn + 1);
  for (int l = 0; l <= ln; l++)
    for (int r = 0; r <= rn; r++)
      res[l + r] = (res[l + r] + 1ll * lhs[l] * rhs[r] % MOD * inv2[l * (rn - r) + (ln - l) * r]) % MOD;
  return res;
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      p[i][j] = inv(2);
    p[i][i] = 1;
  }
  for (int i = 0; i < m; i++)
  {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    u--, v--;
    e[u].push_back(v);
    e[v].push_back(u);
    p[u][v] = 1ll * w * inv(10000) % MOD;
    p[v][u] = 1ll * (10000 - w) * inv(10000) % MOD;
  }

  std::vector<int> ans{1};

  for (int u = 0; u < n; u++)
    if (!vis[u])
    {
      std::vector<int> us;
      dfs(us, u);
      ans = join(ans, solve(us));
    }

  int tot = std::accumulate(ans.begin() + 1, ans.end(), 0ll) % MOD;
  for (int i = 0; i < n * (n - 1); i++)
    tot = 1ll * tot * 10000 % MOD;
  printf("%d\n", tot);

  return 0;
}
