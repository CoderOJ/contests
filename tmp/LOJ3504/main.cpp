#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 3005;

std::vector<int> e[N];
std::vector<int> e_rev[N];

int n, m, q;

void bfs(std::vector<int> e[], int s, int ban, bool vis[])
{
  std::fill(vis, vis + N, false);

  if (s == ban)
    return;

  vis[s] = true;
  std::queue<int> que;
  que.push(s);
  while (!que.empty())
  {
    int u = que.front();
    que.pop();
    for (int v : e[u])
      if (!vis[v] && v != ban)
      {
        vis[v] = true;
        que.push(v);
      }
  }
}

bool is_dominate[N][N];
int  dominate_cnt[N];
int  dominate_fa[N];

std::vector<int> dfn_us;

void calc_dominate_tree()
{
  for (int i = 1; i <= n; i++)
  {
    bfs(e, 1, i, is_dominate[i]);
    for (int j = 1; j <= n; j++)
    {
      is_dominate[i][j] = !is_dominate[i][j];
      // see("dominate", i, j, is_dominate[i][j]);
      if (is_dominate[i][j])
        dominate_cnt[i] += 1;
    }
  }
  std::vector<int> us;
  for (int i = 1; i <= n; i++)
    us.push_back(i);
  std::sort(us.begin(), us.end(), [](int u, int v) {
    return dominate_cnt[u] < dominate_cnt[v];
  });
  for (int u : us)
  {
    for (int v = 1; v <= n; v++)
      if (is_dominate[u][v] && v != u)
      {
        if (dominate_fa[v] == 0)
        {
          dominate_fa[v] = u;
          // see("fa", v, dominate_fa[v]);
        }
      }
  }

  dfn_us = std::vector(us.rbegin(), us.rend());
}

bool rev_visible[N][N];

void calc_rev_visible()
{
  for (int u = 2; u <= n; u++)
    bfs(e_rev, u, dominate_fa[u], rev_visible[u]);
}

bool is_changed[N];

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  q = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    e[u].push_back(v);
    e_rev[v].push_back(u);
  }

  calc_dominate_tree();
  calc_rev_visible();

  for (int i = 0; i < q; i++)
  {
    int s = sc.next_int();
    int t = sc.next_int();

    std::fill(is_changed, is_changed + N, false);
    int ans = 0;
    for (int u : dfn_us)
    {
      if (is_changed[dominate_fa[u]])
      {
        is_changed[u] = true;
        ans += 1;
      }
      else
      {
        int f = dominate_fa[u];
        if (rev_visible[u][t] && !is_dominate[f][s])
        {
          is_changed[u] = true;
          ans += 1;
        }
      }
    }

    printf("%d\n", ans);
  }

  return 0;
}
