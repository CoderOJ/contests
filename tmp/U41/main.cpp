#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 405;

std::vector<int> e[N];

int n, m;
int a[N][N];

int  match[N];
bool vis[N];

std::queue<int> que;

void engage(int u, int v)
{
  if (match[v] == 0 || a[v][u] < a[v][match[v]])
  {
    if (match[v] != 0)
      que.push(match[v]);
    match[match[v]] = 0;
    match[v]        = u;
    match[u]        = v;
  }
  else
  {
    que.push(u);
  }
}

void rmain()
{
  n = sc.next_int();
  m = sc.next_int();

  for (int u = 1; u <= n; u++)
    for (int j = 1; j <= m; j++)
    {
      int v = sc.next_int();
      if (v != 0)
      {
        a[u][n + v] = j;
        a[n + v][u] = -j;
        // see(u, v, +j);
        // see(v, u, -j);
      }
    }

  for (int u = 1; u <= n; u++)
  {
    e[u].clear();
    for (int v = 1; v <= n; v++)
      e[u].push_back(n + v);
    std::sort(e[u].begin(), e[u].end(), [&](int v1, int v2) {
      return a[u][v1] > a[u][v2];
    });
  }

  for (int i = 1; i <= n * 2; i++)
    match[i] = 0;
  for (int i = 1; i <= n; i++)
    que.push(i);
  while (!que.empty())
  {
    int u = que.front();
    que.pop();
    engage(u, e[u].back());
    e[u].pop_back();
  }

  for (int u = 1; u <= n; u++)
    std::cout << match[u] - n << " ";
  std::cout << std::endl;
}

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
    rmain();
  return 0;
}
