#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <numeric>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();

  std::vector<int> a(n);
  std::vector<int> b(n);
  for (int i = 0; i < n; i++)
  {
    a[i] = sc.next_int();
    b[i] = sc.next_int();
  }
  std::vector<int> c(n);
  for (int i = 0; i < n; i++)
    c[i] = std::max(0, a[i] - b[i]);

  std::vector<int> ord(n, 0);
  std::iota(ord.begin(), ord.end(), 0);
  std::sort(ord.begin(), ord.end(), [&](int x, int y) { return c[x] < c[y]; });
  std::vector<std::vector<int>> g0(n);
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    g0[u].emplace_back(v);
    g0[v].emplace_back(u);
  }
  std::vector<std::vector<int>> g(n);
  std::vector<int>              p(n, 0);
  std::iota(p.begin(), p.end(), 0);
  auto find = [&](int x) {
    while (x != p[x])
    {
      x = p[x] = p[p[x]];
    }
    return x;
  };
  std::vector<bool> vis(n, false);
  for (auto u : ord)
  {
    for (auto v : g0[u])
    {
      if (vis[v] && find(v) != u)
      {
        g[u].emplace_back(find(v));
        p[find(v)] = u;
      }
    }
    vis[u] = true;
  }

  std::vector<long long> s(n, 0);
  std::vector<long long> dp(n, 1e18);

  std::function<void(int)> dfs = [&](int u) {
    s[u] = b[u];
    if (g[u].empty())
      dp[u] = std::max(a[u], b[u]);
    else
    {
      for (auto v : g[u])
      {
        dfs(v);
        s[u] += s[v];
      }
      for (auto v : g[u])
        dp[u] = std::min(dp[u], s[u] - s[v] + std::max(dp[v], (long long)c[u]));
    }
  };

  dfs((int)ord.back());
  std::cout << dp[(int)ord.back()] << std::endl;

  return 0;
}
