#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <set>
#include <stack>
#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 2005;
std::vector<int> e[N];
int n, m;

struct path_t
{
  int v, id;
  bool rev;

  path_t(int v, int id, bool rev) : 
    v(v), id(id), rev(rev) {}
  bool operator< (const path_t &rhs) const
  { return std::make_tuple(v, id, rev) < std::make_tuple(rhs.v, rhs.id, rhs.rev); }
};

struct path_ref_t
{
  int ref_id;
  bool rev;
  path_ref_t() =default;
  path_ref_t(int ref_id, bool rev) : 
    ref_id(ref_id), rev(rev) {}
};

std::pair<int,int> path[N];
std::set<path_t> upath[N];
path_ref_t eref[N * 2];
bool has_filled[N];
int eid = 0;

int dep[N], fa[N];
void dfs(int u, int f)
{
  dep[u] = dep[f] + 1; fa[u] = f;
  for (int v: e[u]) if (v != f) dfs(v, u);
}

int next_hop[N][N];
void init_next_hop(int u, int f, int origin, int hop)
{
  next_hop[origin][u] = hop;
  for (int v: e[u]) if (v != f) init_next_hop(v, u, origin, hop);
}
int find_lca(int root, int u, int v)
{
  if (root == u || root == v)
    return root;
  if (next_hop[root][u] != next_hop[root][v])
    return root;
  return find_lca(next_hop[root][u], u, v);
}

void add_edge(int u, int v, int id, bool rev = false)
{
  see("add edge", u, v, id);
  upath[u].emplace(v, id, rev);
  upath[v].emplace(u, id, !rev);
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    e[u].push_back(v);
    e[v].push_back(u);
  }
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    path[eid] = std::make_pair(u, v);        
    add_edge(u, v, eid);
    eid++;
  }
  dfs(1, 0);

  for (int u = 1; u <= n; u++)
    for (int v: e[u]) 
      init_next_hop(v, u, u, v);

  std::vector<int> vs(n - 1);
  for (int i = 0; i < n - 1; i++) vs[i] = i + 2;
  std::sort(vs.begin(), vs.end(), [](int a, int b) { return dep[a] > dep[b]; });

  int ans = 0;
  for (int u: vs)
  {
    int f = fa[u];
    see(u, f, has_filled[u], upath[u].size());

    if (has_filled[u])
    {
      ans += 2;
      for (const auto [v,id,rev] : upath[u])
      {
        upath[v].erase(path_t(u, id, !rev));
        if (v != f)
          add_edge(f, v, id, rev);
      }
    }
    else
    {
      if (upath[u].size() == 0) {}
      else if (upath[u].size() == 1)
      {
        ans += 1;
        const auto [v,id,rev] = *upath[u].begin();
        upath[v].erase(path_t(u, id, !rev));
        if (v == f) 
          eref[id] = path_ref_t(id, false);
        else
          add_edge(f, v, id, rev);
      }
      else
      {
        ans += 2;
        const auto [v0,id0,rev0] = *upath[u].begin();
        see(v0, id0, rev0);
        cm_assert(u != v0);
        upath[u].erase(upath[u].begin());
        upath[v0].erase(path_t(u, id0, !rev0));
        const auto [v1,id1,rev1] = *upath[u].begin();
        see(v1, id1, rev1);
        cm_assert(u != v1);
        upath[u].erase(upath[u].begin());
        upath[v1].erase(path_t(u, id1, !rev1));
        int l = find_lca(u, v0, v1);

        for (int p = u; p != l;)
        {
          int pv = next_hop[p][l];
          if (dep[p] > dep[pv])
            has_filled[p] = true;
          else
            has_filled[pv] = true;
          p = pv;
        }
        
        int cur_eid = eid++;
        eref[id0] = path_ref_t(cur_eid, rev0 ^ true);
        eref[id1] = path_ref_t(cur_eid, rev1);
        if (v0 != v1)
          add_edge(v0, v1, cur_eid);

        for (const auto& [v,id,rev] : upath[u])
        {
          upath[v].erase(path_t(u, id, !rev));
          if (v != f)
            add_edge(f, v, id, rev);
        }
      }
    }
  }

  std::cout << ans << std::endl;
  for (int i = eid - 1; i >= 0; i--)
    eref[i].rev ^= eref[eref[i].ref_id].rev;
  for (int i = 0; i < m; i++)
    if (eref[i].rev)
      std::cout << path[i].first << " " << path[i].second << std::endl;
    else
      std::cout << path[i].second << " " << path[i].first << std::endl;

  return 0;
}

