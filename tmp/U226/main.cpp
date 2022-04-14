#include <bits/stdc++.h>

const int MOD = 998244353;
const int N = 1005;

std::vector<std::pair<int, int>> e[N];
int tot_w[N], n, m;

auto fac = []{
  const int N = 1e7;
  std::array<int, N> res;
  res[0] = 1;
  for (int i = 1; i < N; i++)
    res[i] = 1ll * res[i - 1] * i % MOD;
  return res;
}();

auto inv = []{
  const int N = 1e7;
  std::array<int, N> inv;
  inv[0] = 1;
  inv[1] = 1;
  for (int i = 2; i < N; i++)
    inv[i] = 1ll * inv[MOD % i] * (MOD - MOD / i) % MOD;
  return inv;
}();

auto ifac = []{
  const int N = 1e7;
  std::array<int, N> res;
  res[0] = 1;
  for (int i = 1; i < N; i++)
    res[i] = 1ll * res[i - 1] * inv[i] % MOD;
  return res;
}();

int binom(int n, int m)
{
  if (m < 0 || m > n)
    return 0;
  else
    return 1ll * fac[n] * ifac[n - m] % MOD * ifac[m] % MOD;
}

void solve_tree()
{
  int prod_deg = []{
    int res = 1;
    for (int i = 1; i <= n; i++)
    {
      if (tot_w[i] % 2 == 1)
      {
        return 1;
      }
      else
      {
        res = 1ll * res * fac[tot_w[i] / 2 - 1] % MOD;
      }
    }
    return res;
  }();

  int prod_tree = []{
    int res = 1;
    for (int u = 1; u <= n; u++)
      for (const auto &[v, w] : e[u])
        if (u < v)
        {
          if (w % 2 == 1)
          {
            return 0;
          }
          else
          {
            res = 1ll * res * binom(w, w / 2) % MOD;
            res = 1ll * res * (w / 2) % MOD;
          }
        }
    return res;
  }();

  int ans = 1ll * prod_deg * prod_tree % MOD;
  printf("%d\n", ans);
}

bool vis[N], is_circ[N];
int fa[N], fa_w[N];
std::vector<int> circ_w;

void dfs_find_circle(int u, int f)
{
  vis[u] = true;
  for (const auto &[v, w] : e[u])
    if (v != f)
    {
      if (!vis[v])
      {
        fa[v] = u;
        fa_w[v] = w;
        dfs_find_circle(v, u);
      }
      else
      {
        if (!is_circ[u])
        {
          for (int p = u; p != v; p = fa[p])
          {
            is_circ[p] = true;
            circ_w.push_back(fa_w[p]);
          }
          is_circ[v] = true;
          circ_w.push_back(w);
        }
      }
    }
}

void solve_circle()
{
  int prod_deg = []{
    int res = 1;
    for (int i = 1; i <= n; i++)
    {
      if (tot_w[i] % 2 == 1)
      {
        return 1;
      }
      else
      {
        res = 1ll * res * fac[tot_w[i] / 2 - 1] % MOD;
      }
    }
    return res;
  }();

  dfs_find_circle(1, 0);

  int prod_other_tree = []{
    int res = 1;
    for (int u = 1; u <= n; u++)
      for (const auto &[v, w] : e[u])
        if (u < v && (!is_circ[u] || !is_circ[v]))
        {
          if (w % 2 == 1)
          {
            return 0;
          }
          else
          {
            res = 1ll * res * binom(w, w / 2) % MOD;
            res = 1ll * res * (w / 2) % MOD;
          }
        }
    return res;
  }();

  int prod_circ_tree = []{
    int res = 0;
    int min_w = *std::min_element(circ_w.begin(), circ_w.end());
    for (int x : circ_w)
      if (x % 2 != min_w % 2)
        return 0;

    auto calc_d = [](int d) {
      int cur = 0;

      int r = 1; 
      for (int x : circ_w)
        r = 1ll * r * ((x - d) / 2) % MOD;
      for (int x : circ_w)
      {
        r = 1ll * r * inv[(x - d) / 2] % MOD;
        cur = (cur + r) % MOD;
        r = 1ll * r * ((x + d) / 2) % MOD;
      }

      for (int x : circ_w)
        cur = 1ll * cur * binom(x, (x - d) / 2) % MOD;
      return cur;
    };

    for (int d = -min_w; d < 0; d += 2)
      res = (res + calc_d(d)) % MOD;

    if (min_w % 2 == 1)
      res = (res + res) % MOD;
    else
      res = (0ll + res + res + calc_d(0)) % MOD;

    return res;
  }();

  int ans = 1ll * prod_deg * prod_other_tree % MOD * prod_circ_tree % MOD;
  printf("%d\n", ans);
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++)
  {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
    tot_w[u] += w;
    tot_w[v] += w;
  }

  if (m == n - 1)
    solve_tree();
  else
    solve_circle();

  return 0;
}
