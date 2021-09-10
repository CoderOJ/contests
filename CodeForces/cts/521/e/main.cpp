#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util.hpp"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int B = 20;
constexpr int N = 200005;
std::vector<std::pair<int,int>> es;
std::vector<int> e[N];
int n, m;

int dep[N], fa[N][B];
void dfs(int u, int f)
{
  see(u, f);
  fa[u][0] = f;
  for (int i = 0; i + 1 < B; i++)
    fa[u][i + 1] = fa[fa[u][i]][i];
  dep[u] = dep[f] + 1; 
  for (int v : e[u]) if (dep[v] == -1)
    dfs(v, u);
}

int lca(int u, int v)
{
  if (dep[u] < dep[v]) std::swap(u, v);
  int d = dep[u] - dep[v]; for (int i = 0; i < B; i++) if (d & (1 << i)) u = fa[u][i];
  for (int i = B-1; i >= 0; i--) if (fa[u][i] != fa[v][i]) { u = fa[u][i], v = fa[v][i]; }
  return u == v ? u : fa[u][0];
}

std::vector<int> get_path(int u, int v)
{
  if (dep[u] < dep[v])
  {
    auto res = get_path(v, u) + u;
    std::reverse(res.begin(), res.end());
    res.pop_back();
    return res;
  }
  else
  {
    see(u, v);
    std::vector<int> res;
    for (; u != v; u = fa[u][0])
    {
      see(u);
      res.push_back(u);
    }
    return res;
  }
}

std::pair<int, int> cross_edge[N];

void put_ans(int ua, int va, int ub, int vb)
{
  see(ua, va, ub, vb);
  int ul = lca(ua, ub);
  int dest = dep[va] > dep[vb] ? va : vb;
  auto ans0 = get_path(ul, ua) + ua + get_path(va, dest) + dest; 
  auto ans1 = get_path(ul, ub) + ub + get_path(vb, dest) + dest;
  auto ans2 = get_path(ul, dest) + dest;

  std::ostream_iterator<int> out(std::cout, " ");
  std::cout << "YES" << std::endl;
  std::cout << ans0.size() << " "; std::copy(ans0.begin(), ans0.end(), out); std::cout << std::endl; 
  std::cout << ans1.size() << " "; std::copy(ans1.begin(), ans1.end(), out); std::cout << std::endl;
  std::cout << ans2.size() << " "; std::copy(ans2.begin(), ans2.end(), out); std::cout << std::endl;
  exit(0);
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int(), v = sc.next_int();
    e[u].push_back(v); e[v].push_back(u);
    es.emplace_back(u, v);
  }

  std::fill(dep + 1, dep + n + 1, -1);
  for (int u = 1; u <= n; u++)
    if (dep[u] == -1)
      dfs(u, 0);

  for (auto [u,v] : es)
  {
    if (dep[u] < dep[v]) std::swap(u, v);
    if (dep[u] == dep[v] + 1) continue;
    see(u, v);
    for (int p = u; p != v; p = fa[p][0])
    {
      see(p);
      if (cross_edge[p] == std::make_pair(0,0))
        cross_edge[p] = std::make_pair(u, v);
      else
        put_ans(cross_edge[p].first, cross_edge[p].second, u, v);
    }
  }

  puts("NO");
  return 0;
}

