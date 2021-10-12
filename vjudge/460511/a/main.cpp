#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <queue>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 100005;

int n, m, k;
std::vector<int> be[N], e[N];
int deg[N];
int dis[N][55], disu[N];
std::queue<std::pair<int, int>> que;

void solve()
{
  n = sc.next_int();
  m = sc.next_int();
  k = sc.next_int();
  while (m--)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    be[u].push_back(v);
    be[v].push_back(u);
    e[v].push_back(u);
    deg[u]++;
  }
  for (int i = 1; i <= n; i++)
  {
    for (int j = 0; j <= k; j++)
      dis[i][j] = -1;
    disu[i] = -1;
  }
  dis[n][0] = 0, que.push(std::make_pair(n, 0));
  for (int i = 1; i <= n; i++)
    if (deg[i] == 0)
      deg[i]++, e[i].push_back(i);

  while (!que.empty())
  {
    int u = que.front().first, j = que.front().second;
    que.pop();
    if (j != k)
    {
      for (int v : be[u])
        if (dis[v][j + 1] == -1)
          dis[v][j + 1] = dis[u][j] + 1, que.push(std::make_pair(v, j + 1));
    }
    if (disu[u] == -1)
    {
      disu[u] = dis[u][j];
      for (int v : e[u])
        if (!(--deg[v]))
          dis[v][0] = disu[u] + 1, que.push(std::make_pair(v, 0));
    }
  }

  for (int i = 1; i <= n; i++)
    printf("%d\n", disu[i]);
  for (int i = 1; i <= n; i++)
    be[i].clear(), e[i].clear(), deg[i] = 0;
}

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    printf("Case #%d:\n", i + 1);
    solve();
  }
  return 0;
}
