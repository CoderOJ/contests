#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 200005;

std::vector<int> e[N];
int              n, m;

std::vector<std::pair<int, int>> ans;

bool vis[N];
int  dep[N], det[N];
void dfs(int u, int f)
{
  dep[u] = dep[f] + 1;
  vis[u] = true;
  for (int v : e[u])
    if (v != f)
    {
      if (!vis[v])
        dfs(v, u);
      else if (dep[v] < dep[u])
      {
        ans.emplace_back(v, u);
        det[v] = !det[v];
      }
    }
  if (f != 0)
  {
    if (det[u])
    {
      ans.emplace_back(u, f);
    }
    else
    {
      ans.emplace_back(f, u);
      det[f] = !det[f];
    }
  }
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    e[u].push_back(v);
    e[v].push_back(u);
  }

  for (int u = 1; u <= n; u++)
    if (!vis[u])
    {
      dfs(u, 0);
      if (det[u])
      {
        puts("-1");
        return 0;
      }
    }

  for (const auto &[u, v] : ans)
    std::cout << u << " " << v << std::endl;

  return 0;
}
