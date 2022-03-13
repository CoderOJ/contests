#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1009;
constexpr int M = 200005;

int u[M], v[M];
int n, m;

struct graph_t
{
  std::vector<int> e[N];

  int t[N];

  void init(int s)
  {
    for (int i = 0; i < N; i++)
      e[i].clear();
    std::fill(t, t + N, -1);
    t[s] = m;
  }

  void dfs_mark(int u, int time)
  {
    t[u] = time;
    for (int v : e[u])
      if (t[v] == -1)
        dfs_mark(v, time);
  }

  void add_edge(int u, int v, int time)
  {
    e[u].push_back(v);
    if (t[u] != -1 && t[v] == -1)
      dfs_mark(v, time);
  }
};

graph_t g0, g1;
int     ans[M];

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    u[i] = sc.next_int();
    v[i] = sc.next_int();
  }

  for (int s = 1; s <= n; s++)
  {
    g0.init(s);
    g1.init(s);
    for (int i = m - 1; i >= 0; i--)
      if (u[i] >= s && v[i] >= s)
      {
        g0.add_edge(u[i], v[i], i);
        g1.add_edge(v[i], u[i], i);
      }
    for (int t = 1; t <= n; t++)
      if (g0.t[t] != -1 && g1.t[t] != -1)
        ans[std::min(g0.t[t], g1.t[t])] += 1;
  }

  for (int i = m; i >= 0; i--)
    ans[i] += ans[i + 1];

  for (int i = 0; i <= m; i++)
    printf("%d ", ans[i]);
  puts("");

  return 0;
}
