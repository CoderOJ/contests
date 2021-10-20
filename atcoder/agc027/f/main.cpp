#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#include <string>

cm::scanner<cm::optimal_reader> sc(stdin);

struct tree_t
{
  std::vector<std::vector<int>> e;
  int n, root;

  std::vector<int> fa = std::vector<int>(e.size(), 0);
  std::vector<int> sons = std::vector<int>(e.size(), 0);

  void dfs_init_fa(int u, int f)
  {
    sons[u] = 0;
    fa[u] = f;
    for (int v : e[u])
      if (v != f)
      {
        sons[u]++;
        dfs_init_fa(v, u);
      }
  }

  tree_t(int n) : e(n + 1), n(n), root(-1)
  {
  }
  void set_root(int root)
  {
    this->root = root;
    dfs_init_fa(root, 0);
  }
  void add_edge(int u, int v)
  {
    cm_assert(u <= n && v <= n, u, v, n);
    e[u].push_back(v);
    e[v].push_back(u);
  }
  bool is_leaf(int u)
  {
    return sons[u] == 0;
  }
  int get_fa(int u)
  {
    return fa[u];
  }
  void relink(int u, int f)
  {
    sons[fa[u]]--;
    fa[u] = f;
    sons[fa[u]]--;
  }
  void relink_force(int u, int f)
  {
    int of = e[u][0];
    e[of].erase(std::find(e[of].begin(), e[of].end(), u));
    e[u][0] = f;
    e[f].push_back(u);
  }
};

int main()
{
  auto solve = [] {
    int n = sc.next_int();
    tree_t ta(n), tb(n);

    auto scan_tree = [&](tree_t &t) {
      for (int i = 1; i < n; i++)
        t.add_edge(sc.next_int(), sc.next_int());
    };
    scan_tree(ta);
    scan_tree(tb);

    auto is_error = [&](int u) { return ta.get_fa(u) != tb.get_fa(u); };

    auto is_movable = [&](int u) {
      return ta.is_leaf(u) && !is_error(tb.get_fa(u));
    };

    auto get_times = [&](int u) mutable {
      see(u);
      int cur_ans = 0;
      ta.set_root(u);
      tb.set_root(u);
      while (true)
      {
        bool have_error = false;
        bool have_moved = false;
        for (int v = 1; v <= n; v++)
          if (is_error(v))
          {
            see(v, ta.get_fa(v), tb.get_fa(v), is_movable(v));
            have_error = true;
            if (is_movable(v))
            {
              cur_ans++;
              see(v, "->", tb.get_fa(v));
              ta.relink(v, tb.get_fa(v));
              have_moved = true;
            }
          }
        if (!have_error)
          return cur_ans;
        if (have_error && !have_moved)
          return n + 1;
      }
    };

    int ans = n + 1;
    for (int u = 1; u <= n; u++)
      check_min(ans, get_times(u));


    for (int r = 1; r <= n; r++)
      if (ta.e[r].size() == 1)
      {
        int of = ta.e[r][0];
        for (int v = 1; v <= n; v++)
          if (v != r && v != of)
          {
            ta.relink_force(r, v);
            check_min(ans, get_times(r) + 1);
            ta.relink_force(r, of);
          }
      }

    return ans >= n + 1 ? -1 : ans;
  };

  int t = sc.next_int();
  for (int i = 0; i < t; i++)
    printf("%d\n", solve());
  return 0;
}
