#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();
    int c = sc.next_int() - 1;

    std::vector<std::vector<int>> e(n);
    for (int i = 0; i < n - 1; i++)
    {
      int u = sc.next_int() - 1;
      int v = sc.next_int() - 1;
      e[u].push_back(v);
      e[v].push_back(u);
    }

    int m = sc.next_int();

    std::vector<int> path(m);
    for (int i = 0; i < m; i++)
      path[i] = sc.next_int() - 1;

    auto fa = [&] {
      std::vector<int> a(n);
      cm::y_combinate([&](auto &&self, int u, int f) -> void {
        a[u] = f;
        for (int v: e[u])
          if (v != f)
            self(v, u);
      })(0, -1);
      return a;
    }();

    std::vector<double> dpv(n, 0);
    std::vector<double> dps(n, 0);

    auto set_dpv = [&](int u, double v) {
      if (fa[u] != -1)
        dps[fa[u]] -= dpv[u];
      dpv[u] = v;
      if (fa[u] != -1)
        dps[fa[u]] += dpv[u];
    };

    auto get_dpr = [&](int u) {
      double res = dps[u];
      if (fa[u] != -1)
        res += dpv[fa[u]];
      return res;
    };

    for (int i = m - 1; i >= 0; i--)
    {
      int  u = path[i];
      auto w = get_dpr(u) / (double)e[u].size() + 1;
      set_dpv(u, w);
    }

    printf("%.15lf\n", dpv[c]);
  }
  return 0;
}
