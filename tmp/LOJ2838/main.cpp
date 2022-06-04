#include "/home/jack/cm/debug"
#include "/home/jack/cm/proof.hpp"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <limits>
#include <queue>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 100005, 105)
CONSTRAINT(B, 100, 5)

using vert = cm::proof::int_index<0, N>;

cm::proof::index_array<vert, std::vector<vert>> e;
cm::proof::index_array<vert, std::vector<vert>> eb;

using disv_t = std::vector<std::pair<vert, int>>;
disv_t join(const disv_t &lhs, const disv_t &rhs)
{
  static cm::proof::index_array<vert, bool> vis;

  disv_t res;
  for (auto it_l = lhs.begin(), it_r = rhs.begin();
       it_l != lhs.end() || it_r != rhs.end();)
  {
    if (it_r == rhs.end() || (it_l != lhs.end() && it_l->second > it_r->second))
    {
      if (!vis[it_l->first])
      {
        vis[it_l->first] = true;
        res.push_back(*it_l);
      }
      it_l++;
    }
    else
    {
      if (!vis[it_r->first])
      {
        vis[it_r->first] = true;
        res.push_back(*it_r);
      }
      it_r++;
    }
  }

  for (const auto &[u, ud] : res)
    vis[u] = false;

  return res;
}

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  int q = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    vert u{sc.next_int()};
    vert v{sc.next_int()};
    e[v].push_back(u);
    eb[u].push_back(v);
  }

  static cm::proof::index_array<vert, disv_t> dtop;
  for (vert u : vert::all(1, n + 1))
  {
    for (vert v : e[u])
    {
      dtop[u] = join(dtop[u], dtop[v]);
      if (dtop[u].size() > B)
        dtop[u].resize(B);
    }
    for (auto &[v, vd] : dtop[u])
      vd += 1;
    if (dtop[u].size() < B)
      dtop[u].emplace_back(u, 0);
  }

  static cm::proof::index_array<vert, bool> ava;
  std::fill(ava.begin(), ava.end(), true);
  for (int i = 0; i < q; i++)
  {
    vert s{sc.next_int()};

    int               k = sc.next_int();
    std::vector<vert> us;
    for (int i = 0; i < k; i++)
      us.push_back(vert{sc.next_int()});
    for (vert u : us)
      ava[u] = false;

    if (k < B)
    {
      int ans = -1;
      for (const auto &[u, ud] : dtop[s])
        if (ava[u])
          check_max(ans, ud);
      printf("%d\n", ans);
    }
    else
    {
      static cm::proof::index_array<vert, int> dis;
      std::fill(dis.begin(), dis.end(), std::numeric_limits<int>::min());
      dis[s] = 0;
      for (int u_val = n; u_val >= 1; u_val--)
      {
        vert u{u_val};
        if (dis[u] >= 0)
          for (vert v : e[u])
            check_max(dis[v], dis[u] + 1);
      }

      int ans = -1;
      for (vert u : vert::all(1, n + 1))
      {
        if (ava[u])
          check_max(ans, dis[u]);
      }
      printf("%d\n", ans);
    }

    for (vert u : us)
      ava[u] = true;
  }

  return 0;
}
