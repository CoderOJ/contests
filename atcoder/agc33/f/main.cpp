#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstring>
#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 2005;

std::vector<int> e[N];

int n, m;

int  fa[N][N];
void dfs_init(int u, int f, int a)
{
  fa[a][u] = f;
  for (int v : e[u])
    if (v != f)
      dfs_init(v, u, a);
}

int bel[N][N];

std::queue<std::pair<int, int>> que;

void dfs_mark_bel(int u, int r, int a)
{
  see(u, r, a);
  if (bel[r][u] == -1)
  {
    bel[r][u] = a;
    for (int v : e[u])
      if (v != fa[r][u])
        dfs_mark_bel(v, r, a);
  }
  else
  {
    que.emplace(a, u);
  }
}

int calc(int u, int r, int p)
{
  see(u, r, p, bel[r][u]);
  int ans = 0;
  if (bel[p][u] == u)
  {
    ans = 1;
    p   = u;
  }
  for (int v : e[u])
    if (v != fa[r][u])
    {
      ans += calc(v, r, p);
    }
  return ans;
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
    que.emplace(u, v);
  }

  for (int i = 1; i <= n; i++)
    dfs_init(i, 0, i);
  memset(bel, -1, sizeof(bel));

  while (!que.empty())
  {
    const auto [u, v] = que.front();
    que.pop();
    see(u, v);

    if (bel[u][v] == v)
      continue;
    if (bel[u][v] != -1)
      que.emplace(bel[u][v], v);
    else if (bel[v][u] != -1)
      que.emplace(bel[v][u], u);
    else
    {
      dfs_mark_bel(v, u, v);
      dfs_mark_bel(u, v, u);
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; i++)
  {
    ans += calc(i, i, i);
    see(i, ans);
  }

  printf("%d\n", ans / 2);

  return 0;
}
