#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <bitset>
#include <map>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1005;

int  m, n, p[N], id[N];
bool ok[N], vis[N];

std::vector<int> e[8][N];

struct point_t
{
  int x, y;
} a[N], b[N];

bool straight(point_t u, point_t v, point_t w)
{
  if (1ll * (v.x - u.x) * (w.y - v.y) != 1ll * (v.y - u.y) * (w.x - v.x))
    return false;
  if (!(std::min(u.x, w.x) <= v.x && v.x <= std::max(u.x, w.x)))
    return false;
  if (!(std::min(u.y, w.y) <= v.y && v.y <= std::max(u.y, w.y)))
    return false;
  return true;
}

void dfs(int &k, int i)
{
  if (k >= m)
    return;
  int _p = p[k];
  for (auto j : e[_p][i])
  {
    if (!vis[j])
    {
      dfs(++k, j);
      if (k >= m)
        return;
    }
  }
  id[_p] = i;
  vis[i] = true;
}

int main()
{
  m = sc.next_int();
  n = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    a[i].x = sc.next_int();
    a[i].y = sc.next_int();
  }
  for (int i = 0; i < n; i++)
  {
    b[i].x = sc.next_int();
    b[i].y = sc.next_int();
  }

  for (int k = 0; k < m; k++)
  {
    p[k] = k;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
      {
        if (i == j)
          continue;
        if (straight(a[k], b[j], b[i]))
        {
          e[k][i].push_back(j);
          if ((int)e[k][i].size() >= m)
            break;
        }
      }
  }

  do
  {
    for (int i = 0; i < n; i++)
    {
      if (ok[i])
        continue;
      int k = 0;
      dfs(k, i);
      ok[i] = k < m;
      for (k = 0; k < m; k++)
        vis[id[k]] = false;
    }
  } while (std::next_permutation(p, p + m));

  int ans = 0;
  for (int i = 0; i < n; i++)
    ans += ok[i];
  printf("%d\n", ans);

  return 0;
}
