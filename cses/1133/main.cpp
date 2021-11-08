#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <functional>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  CONSTRAINT(B, 20, 20)

  int n = sc.next_int();
  std::vector<std::vector<int>> e(n);
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  std::vector<long long> cnt(n, 1), sum(n, 0);
  std::function<void(int, int)> dfs0 = [&](int u, int f) {
    for (int v : e[u])
      if (v != f)
      {
        dfs0(v, u);
        cnt[u] += cnt[v];
        sum[u] += sum[v] + cnt[v];
      }
  };
  dfs0(0, 0);

  std::vector<long long> ans(n);
  std::function<void(int, int, long long)> dfs1 = [&](int u, int f, long long psum) {
    psum += n - cnt[u];
    ans[u] = sum[u] + psum;
    for (int v : e[u]) if (v != f)
      dfs1(v, u, ans[u] - (sum[v] + cnt[v]));
  };
  dfs1(0, 0, 0);

  for (int i = 0; i < n; i++)
    std::cout << ans[i] << " ";

  return 0;
}
