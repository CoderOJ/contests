#include "/home/jack/cm/debug"
#include "/home/jack/cm/proof"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

using namespace cm::proof;

constexpr int N = 1'000'005;

using vert = int_index<0, N>;
index_array<vert, std::vector<vert>> e;
index_array<vert, int>               ww, w;

int n;

void dfs_assign_w(vert u, vert f, int dep, int oc)
{
  w[u] = (dep % 2 == oc) ? ww[u] : 0;
  for (vert v : e[u])
    if (v != f)
      dfs_assign_w(v, u, dep + 1, oc);
}

index_array<vert, int64_t> dp;

int64_t ans;

void dfs_dp(vert u, vert f)
{
  int64_t cur = w[u];
  for (vert v : e[u])
    if (v != f)
      cur += w[v];
  dp[u] = cur;
  check_max(ans, cur);
  for (vert v : e[u])
    if (v != f)
    {
      dfs_dp(v, u);
      check_max(ans, dp[u] - w[v] + dp[v] + w[f]);
      check_max(dp[u], cur - w[v] + dp[v]);
    }
}

int main()
{
  n = sc.next_int();
  for (int i = 1; i <= n; i++)
    ww[vert(i)] = sc.next_int();
  for (int i = 1; i < n; i++)
  {
    vert u(sc.next_int());
    vert v(sc.next_int());
    e[u].push_back(v);
    e[v].push_back(u);
  }

  vert root(1);
  vert root_f(0);
  dfs_assign_w(root, root_f, 0, 0);
  dfs_dp(root, root_f);
  dfs_assign_w(root, root_f, 0, 1);
  dfs_dp(root, root_f);

  std::cout << ans << std::endl;

  return 0;
}
