#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <cmath>

cm::scanner<cm::optimal_reader> sc(stdin);

const int N = 200005;
int n, w[N], s[N], rt, v[N], ans1;
std::vector<std::pair<int, int>> e[N];
double sum, sd, d[N], ans2 = 1e20;

void dfs(int x, int f, int S)
{
  s[x] = 1;
  int o = 0;
  for (size_t i = 0; i < e[x].size(); i++)
  {
    int y = e[x][i].first;
    if (v[y] || y == f)
      continue;
    dfs(y, x, S);
    s[x] += s[y];
    check_max(o, s[y]);
  }
  o = std::max(o, S - s[x]);
  if (o <= (S >> 1))
    rt = x;
}

void calc(int x, int f, int o, int z)
{
  sum += std::pow(z, 1.5) * w[x];
  d[o] += pow(z, 0.5) * 1.5 * w[x];
  for (size_t i = 0; i < e[x].size(); i++)
  {
    int y = e[x][i].first;
    if (y == f)
      continue;
    calc(y, x, o, z + e[x][i].second);
  }
}

void dfs(int x, int S)
{
  dfs(x, 0, S), x = rt, dfs(x, 0, S);
  if (v[x])
    return;
  v[x] = 1, sum = sd = 0;
  for (size_t i = 0; i < e[x].size(); i++)
  {
    int y = e[x][i].first;
    d[y] = 0, calc(y, x, y, e[x][i].second), sd += d[y];
  }
  if (sum < ans2)
    ans1 = x, ans2 = sum;
  for (size_t i = 0; i < e[x].size(); i++)
  {
    int y = e[x][i].first;
    if (sd - d[y] * 2 >= 0)
      continue;
    dfs(y, s[y]);
    break;
  }
}

int main()
{
  n = sc.next_int();
  for (int i = 1; i <= n; i++)
    w[i] = sc.next_int();
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    int w = sc.next_int();
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
  }

  dfs(1, n);
  printf("%d %.18f\n", ans1, ans2);

  return 0;
}
