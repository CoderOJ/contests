#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 100005;

std::pair<long long, int> dt[N];
std::pair<int, int>       edge[N];
std::vector<int>          e[N];

long long dis[N];
int       n, size[N], tot;

void dfs(int u, int fa)
{
  for (int v : e[u])
    if (v != fa)
    {
      dis[v] = dis[u] + 1;
      dfs(v, u);
    }
}

int main()
{
  n = sc.next_int();

  for (int i = 1; i <= n; i++)
  {
    long long d = sc.next_long();
    dt[i]       = {d, i};
    size[i]     = 1;
  }

  std::sort(dt + 1, dt + n + 1);
  std::reverse(dt + 1, dt + n + 1);

  for (int i = 1; i < n; i++)
  {
    long long delta = dt[i].first - n + 2 * size[i];
    int       l = 1, r = n + 1, pos = 0;
    while (l <= r)
    {
      int mid = (l + r) >> 1;
      if (dt[mid].first <= delta)
      {
        r   = mid - 1;
        pos = mid;
      }
      else
        l = mid + 1;
    }
    if (dt[pos].first != delta)
    {
      puts("-1");
      return 0;
    }

    int u = dt[i].second;
    int v = dt[pos].second;
    e[u].push_back(v);
    e[v].push_back(u);
    edge[++tot] = {u, v};
    size[pos] += size[i];
  }

  dfs(dt[n].second, 0);
  long long sum = 0;
  for (int i = 1; i <= n; i++)
    sum += dis[i];
  if (sum == dt[n].first)
    for (int i = 1; i <= tot; i++)
      std::cout << edge[i].first << " " << edge[i].second << std::endl;
  else
    puts("-1");

  return 0;
}
