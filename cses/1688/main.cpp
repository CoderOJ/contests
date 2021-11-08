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
  int q = sc.next_int();
  std::vector<std::vector<int>> e(n);
  for (int i = 1; i < n; i++)
    e[sc.next_int() - 1].push_back(i); 

  std::vector<int> dep(n);
  std::vector<std::vector<int>> fa(n, std::vector<int>(B));
  std::function<void(int, int)> dfs = [&](int u, int f) {
    dep[u] = dep[f] + 1;
    fa[u][0] = f;
    for (int i = 0; i + 1 < B; i++)
      fa[u][i + 1] = fa[fa[u][i]][i];
    for (int v : e[u])
      if (v != f)
        dfs(v, u);
  };
  dfs(0, 0);

  auto lca = [&](int u, int v) {
    if (dep[u] < dep[v])
      std::swap(u, v);
    int d = dep[u] - dep[v];
    for (int i = 0; i < B; i++)
      if (d & (1 << i))
        u = fa[u][i];
    for (int i = B-1; i >= 0; i--)
      if (fa[u][i] != fa[v][i])
        u = fa[u][i], v = fa[v][i];
    return u == v ? u : fa[u][0];
  };

  for (int i = 0; i < q; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    printf("%d\n", lca(u, v) + 1);
  }

  return 0;
}
