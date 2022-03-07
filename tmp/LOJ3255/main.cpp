#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N   = 205;
constexpr int M   = 50'005;
constexpr int INF = 0x3f3f3f3f;

struct edge_item_t
{
  int     u, v;
  int64_t w, d;
};

edge_item_t es[M];

struct edge_t
{
  int     v;
  int64_t w;
  int     id;
};

std::vector<edge_t> ea[N];
std::vector<edge_t> eb[N];

int n, m;

int64_t da_from_1[N];
int64_t da_from_n[N];
int64_t db_from_1[N];
int64_t db_from_n[N];
int64_t tda_from_1[N];
int64_t tda_from_n[N];

int pa_from_1[N];
int pa_from_n[N];

std::set<int> p_edges;

void dijkstra(std::vector<edge_t> e[], int s, int64_t dis[], int *pre)
{
  static bool vis[N];

  std::fill(vis + 1, vis + n + 1, false);
  std::fill(dis + 1, dis + n + 1, INF);
  dis[s] = 0;

  while (true)
  {
    int u = [&] {
      int64_t min_dis = INF;
      int     min_ver = -1;
      for (int i = 1; i <= n; i++)
        if (vis[i] == false && check_min(min_dis, dis[i]))
          min_ver = i;
      return min_ver;
    }();
    if (u == -1)
      break;
    vis[u] = true;
    for (const edge_t &i : e[u])
      if (check_min(dis[i.v], dis[u] + i.w))
        if (pre != nullptr)
          pre[i.v] = i.id;
  }
}

void init_dis()
{
  dijkstra(ea, 1, da_from_1, pa_from_1);
  dijkstra(ea, n, da_from_n, pa_from_n);
  dijkstra(eb, 1, db_from_1, nullptr);
  dijkstra(eb, n, db_from_n, nullptr);
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    int w = sc.next_int();
    int d = sc.next_int();
    ea[u].push_back({v, w, i});
    eb[v].push_back({u, w, i});
    es[i] = {u, v, w, d};
  }

  for (int i = 1; i <= n; i++)
  {
    ea[i].reserve(ea[i].size() * 2);
    eb[i].reserve(eb[i].size() * 2);
  }

  init_dis();

  for (int i = 1; i <= n; i++)
  {
    p_edges.insert(pa_from_1[i]);
    p_edges.insert(pa_from_n[i]);
  }

  int64_t ans = da_from_1[n] + da_from_n[1];

  for (int i = 0; i < m; i++)
  {
    see(i);
    const auto &[u, v, w, d] = es[i];
    if (p_edges.find(i) == p_edges.end())
    {
      int64_t d1n = std::min(da_from_1[n], da_from_1[v] + db_from_n[u] + w);
      int64_t dn1 = std::min(da_from_n[1], da_from_n[v] + db_from_1[u] + w);
      see(d, d1n, dn1);
      check_min(ans, d + d1n + dn1);
    }
    else
    {
      edge_t *ea_pos = nullptr;
      edge_t *eb_pos = nullptr;
      for (int u = 1; u <= n; u++)
      {
        for (auto &e : ea[u])
          if (e.id == i)
            ea_pos = &e;
        for (auto &e : eb[u])
          if (e.id == i)
            eb_pos = &e;
      }

      cm_assert(ea_pos != nullptr, i);
      cm_assert(eb_pos != nullptr, i);

      ea_pos->w = INF;
      eb_pos->w = INF;
      ea[v].push_back({u, w, i});
      eb[u].push_back({v, w, i});
      dijkstra(ea, 1, tda_from_1, nullptr);
      dijkstra(ea, n, tda_from_n, nullptr);

      check_min(ans, d + tda_from_1[n] + tda_from_n[1]);
      see(d, da_from_1[n], da_from_n[1]);

      ea_pos->w = w;
      eb_pos->w = w;
      ea[v].pop_back();
      eb[u].pop_back();
    }
  }

  std::cout << (ans >= INF ? -1 : ans) << std::endl;

  return 0;
}
