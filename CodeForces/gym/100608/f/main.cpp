#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

constexpr int N = 1005;

std::vector<int> e[N];

int col[N];
int adj_col[N];
int n;

void mark_color(int u)
{
  std::set<int> adjs;
  for (int v : e[u])
    if (col[v] > 0)
      adjs.emplace(col[v]);
  for (int i = 1; i <= 4; i++)
    if (!adjs.count(i))
    {
      col[u] = i;
      break;
    }
  for (int v : e[u])
    adj_col[v] += 1;
  std::cout << u << " " << col[u] << std::endl;
}

int main()
{
  int n;
  std::cin >> n;
  for (int i = 1; i < n; i++)
  {
    int u, v;
    std::cin >> u >> v;
    e[u].emplace_back(v);
    e[v].emplace_back(u);
  }

  while (true)
  {
    int max_cnt = 0;
    int max_u   = 0;
    for (int u = 1; u <= n; u++)
      if (col[u] == 0 && adj_col[u] >= max_cnt)
      {
        max_cnt = adj_col[u];
        max_u   = u;
      }
    mark_color(max_u);
    int u, c;
    std::cin >> u >> c;
    if (u == -1 && c == -1)
      break;
    col[u] = c;
    for (int v : e[u])
      adj_col[v]++;
  }

  return 0;
}
