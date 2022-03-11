#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct dsu_t
{
  std::vector<int> p;

  dsu_t(int n) : p(n)
  {
    for (int i = 0; i < n; i++)
      p[i] = i;
  }
  int get(int u)
  {
    return u == p[u] ? u : p[u] = get(p[u]);
  }
  void join(int u, int v)
  {
    u = get(u);
    v = get(v);
    if (u > v)
      std::swap(u, v);
    p[v] = u;
  }
};

int main()
{
  int d = sc.next_int();
  int n = sc.next_int();

  std::vector<std::vector<std::tuple<int, int, int>>> trees;
  for (int i = 0; i < d; i++)
  {
    std::vector<std::tuple<int, int, int>> tree;
    for (int i = 1; i < n; i++)
    {
      int u = sc.next_int() - 1;
      int v = sc.next_int() - 1;
      int w = sc.next_int();
      tree.emplace_back(w, u, v);
    }
    std::sort(tree.begin(), tree.end(), std::greater<>());
    trees.emplace_back(std::move(tree));
  }

  std::vector<std::vector<std::pair<int, std::vector<std::tuple<int, int>>>>>
      ops;

  for (auto &t : trees)
  {
    std::vector<std::pair<int, std::vector<std::tuple<int, int>>>> t_ops;

    dsu_t dsu(n);
    for (auto it_l = t.begin(), it_r = it_l; it_l != t.end(); it_l = it_r)
    {
      while (it_r != t.end() && std::get<0>(*it_r) == std::get<0>(*it_l))
        it_r++;
      for (auto it = it_l; it != it_r; it++)
      {
        auto &[w, u, v] = *it;
        u               = dsu.get(u);
        v               = dsu.get(v);
      }
      for (auto it = it_l; it != it_r; it++)
      {
        auto &[w, u, v] = *it;
        dsu.join(u, v);
      }
      std::vector<std::tuple<int, int>> cur;
      for (auto it = it_l; it != it_r; it++)
      {
        auto &[w, u, v] = *it;
        cur.emplace_back(u, dsu.get(u));
        cur.emplace_back(v, dsu.get(v));
      }
      std::sort(cur.begin(), cur.end());
      cur.erase(std::unique(cur.begin(), cur.end()), cur.end());
      t_ops.emplace_back(std::get<0>(*it_l), std::move(cur));
    }

    ops.emplace_back(std::move(t_ops));
  }

  // see(ops);

  std::vector<int> ids(d);
  for (int i = 0; i < d; i++)
    ids[i] = i;
  std::sort(ids.begin(), ids.end(), [&](int x, int y) {
    return ops[x] != ops[y] ? ops[x] < ops[y] : x < y;
  });

  std::vector<int> ans(d);
  ans[ids[0]] = ids[0];
  for (int i = 1; i < d; i++)
    ans[ids[i]] = ops[ids[i - 1]] == ops[ids[i]] ? ans[ids[i - 1]] : ids[i];

  for (int i = 0; i < d; i++)
    std::cout << ans[i] + 1 << " ";
  std::cout << std::endl;

  return 0;
}
