#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <queue>
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 100000;

std::set<int> e[N];

char col[N];
int  w[N];
int  n;

int  height[N];
int  diameter;
void dfs(int u, int f)
{
  height[u] = w[u];
  for (int v : e[u])
    if (v != f)
    {
      dfs(v, u);
      check_max(diameter, height[u] + height[v]);
      check_max(height[u], height[v] + w[u]);
    }
  check_max(diameter, height[u]);
}

int main()
{
  n = sc.next_int();
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u].insert(v);
    e[v].insert(u);
  }

  sc.next_token(col);

  std::queue<int> ones;
  for (int i = 0; i < n; i++)
    if (e[i].size() == 1)
      ones.push(i);
  while (!ones.empty())
  {
    int u = ones.front();
    ones.pop();
    if (col[u] == 'B' && !e[u].empty())
    {
      int v = *e[u].begin();
      e[v].erase(u);
      e[u].erase(v);
      if (e[v].size() == 1)
        ones.push(v);
    }
  }

  int ans  = -2;
  int root = 0;
  for (int i = 0; i < n; i++)
    if (!e[i].empty() || col[i] == 'W')
    {
      root   = i;
      ans    = ans + 2;
      char c = col[i];
      if (e[i].size() % 2 == 1)
      {
        if (c == 'W')
        {
          w[i] = 0;
        }
        else
        {
          ans++;
          w[i] = 2;
        }
      }
      else
      {
        if (c == 'W')
        {
          ans++;
          w[i] = 2;
        }
        else
        {
          w[i] = 0;
        }
      }
    }

  if (ans == -2)
  {
    puts("0");
    return 0;
  }
  else if (ans == 1)
  {
    puts("1");
    return 0;
  }

  dfs(root, root);

  std::cout << ans - diameter << std::endl;

  return 0;
}
