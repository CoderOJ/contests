#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <bitset>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1005;
std::bitset<1024> f[N], g[N];
std::bitset<1024> vis, dn, tmp, ttmp;
int n;

int main()
{
  n = sc.next_int();
  if (n == 1) return 0;
  if (n == 2) return puts("1 2"), 0;
  for (int i = 1; i <= n; ++i)
  {
    int k = sc.next_int();
    for (int j = 1; j <= k; ++j)
      f[i][sc.next_int()] = 1;
  }

  int flag = 0;
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= n; ++j)
    {
      tmp = f[i] & f[j];
      if (tmp.count() != 2)
        continue;
      int u[2], c = 0;
      for (int k = 1; k <= n; ++k)
        if (tmp[k])
          u[c++] = k;
      if (!g[u[0]][u[1]])
      {
        vis[u[0]] = vis[u[1]] = g[u[0]][u[1]] = g[u[1]][u[0]] = 1;
        printf("%d %d\n", u[0], u[1]);
        flag++;
      }
    }
  }

  if (!flag)
  {
    for (int i = 2; i <= n; ++i)
      printf("1 %d\n", i);
    return 0;
  }

  if (flag == 1)
  {
    int u[2], c = 0;
    for (int i = 1; i <= n; ++i)
      if (vis[i])
        u[c++] = i;
    for (int i = 1; i <= n; ++i)
    {
      if ((int)f[i].count() < n)
      {
        for (int j = 1; j <= n; ++j)
          if (!vis[j])
            printf("%d %d\n", j, u[f[i][j]]);
        break;
      }
    }
    return 0;
  }

  for (int i = 1; i <= n; ++i)
    if (vis[i])
      g[i][i] = dn[i] = 1;
  for (int i = 1; i <= n; ++i)
    if (!dn[i])
    {
      tmp.set();
      for (int j = 1; j <= n; ++j)
        if (f[j][i] && f[j].count() < tmp.count())
          tmp = f[j];
      ttmp = tmp & (~vis);
      tmp = tmp & vis;
      for (int j = 1; j <= n; ++j)
        if (tmp == g[j])
          for (int k = 1; k <= n; ++k)
            if (ttmp[k])
            {
              dn[k] = true;
              printf("%d %d\n", j, k);
            }
    }
  return 0;
}
