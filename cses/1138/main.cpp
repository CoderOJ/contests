#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <functional>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
#define int long long

  struct ftree_t
  {
    std::vector<int> a;
    int n = 0;

    ftree_t() = default;
    ftree_t(int n) : a(n + 1), n(n)
    {
    }

    void modify(int p, int d)
    {
      p += 1;
      for (; p <= n; p += p & (-p))
        a[p] += d;
    }

    int query(int p)
    {
      int res = 0;
      for (; p; p -= p & (-p))
        res += a[p];
      return res;
    }

    int query(int pl, int pr)
    {
      return query(pr) - query(pl);
    }
  };

  int n = sc.next_int();
  int q = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  std::vector<std::vector<int>> e(n);
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  std::vector<int> dfn_l(n), dfn_r(n);
  int cur_dfn = 0;
  std::function<void(int, int)> dfs_init_dfn = [&](int u, int f) {
    dfn_l[u] = cur_dfn;
    cur_dfn += 1;
    for (int v : e[u])
      if (v != f)
        dfs_init_dfn(v, u);
    dfn_r[u] = cur_dfn;
    cur_dfn++;
  };
  dfs_init_dfn(0, 0);

  ftree_t ft(n * 2);
  for (int i = 0; i < n; i++)
  {
    ft.modify(dfn_l[i], a[i]);
    ft.modify(dfn_r[i], -a[i]);
  }

  for (int i = 0; i < q; i++)
  {
    int op = sc.next_int();
    if (op == 1)
    {
      int u = sc.next_int() - 1;
      int x = sc.next_int();
      ft.modify(dfn_l[u], x - a[u]);
      ft.modify(dfn_r[u], -(x - a[u]));
      a[u] = x;
    }
    else
    {
      int u = sc.next_int() - 1;
      printf("%lld\n", ft.query(dfn_r[u]));
    }
  }

  return 0;
}
