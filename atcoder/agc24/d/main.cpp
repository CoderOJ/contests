#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <cstring>
#include <limits>
#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 105;
std::vector<int> e[N];
int n;

int dep[N], max_deg[N];
void dfs(int u, int f, int d)
{
  dep[u] = d;
  check_max(max_deg[dep[u]], static_cast<int>(e[u].size()) - (f != 0));
  for (int v: e[u]) if (v != f) dfs(v, u, d + 1);
}

int main()
{
  n = sc.next_int();
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    e[u].push_back(v);
    e[v].push_back(u);
  }

  std::pair<int, long long> ans(std::numeric_limits<int>::max(), 0);

  for (int u = 1; u <= n; u++)
  {
    memset(dep, 0, sizeof(dep));
    memset(max_deg, 0, sizeof(max_deg));
    dfs(u, 0, 1);
    std::pair<int, long long> cur(0, 1);
    cur.first = *std::max_element(dep + 1, dep + n + 1);
    for (int i = 1; i < cur.first; i++)
      cur.second *= max_deg[i];
    check_min(ans, cur);
    see(u, cur);
  }

  for (int u = 1; u <= n; u++)
    for (int v: e[u]) if (v > u)
    {
      memset(dep, 0, sizeof(dep));
      memset(max_deg, 0, sizeof(max_deg));
      dfs(u, v, 1);
      dfs(v, u, 1);
      std::pair<int, long long> cur(0, 2);
      cur.first = *std::max_element(dep + 1, dep + n + 1);
      for (int i = 1; i < cur.first; i++)
        cur.second *= max_deg[i];
      check_min(ans, cur);
      see(u, v, cur);
    }

  std::cout << ans.first << " " << ans.second << std::endl;

  return 0;
}

