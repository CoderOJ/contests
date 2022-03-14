#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstring>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 305;

int a[N][N];
int n, m;

int64_t t[N][N];
int64_t dis[N * 2];
int64_t e0[N * 2][N * 2];
int64_t e1[N * 2][N * 2];

void set_range(int u, int v, int64_t l, int64_t r)
{
  see(u, v, -l);
  see(v, u, r);
  check_min(e0[u][v], -l);
  check_min(e1[v][u], r);
}

void rmain()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 1; i < n; i++)
    for (int j = 1; j < m; j++)
      a[i][j] = sc.next_int();

  for (int i = 0; i < n; i++)
    t[i][0] = 0;
  for (int j = 0; j < m; j++)
    t[0][j] = 0;
  for (int i = 1; i < n; i++)
    for (int j = 1; j < m; j++)
      t[i][j] = a[i][j] - t[i - 1][j] - t[i][j - 1] - t[i - 1][j - 1];

  memset(e0, 0x3f, sizeof(e0));
  memset(e1, 0x3f, sizeof(e1));
  memset(dis, 0, sizeof(dis));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
    {
      int64_t l = 0 - t[i][j];
      int64_t r = l + 1000000;
      if ((i + j) % 2 == 0)
        set_range(i, j, l, r);
      else
        set_range(i, j, -r, -l);
    }

  bool last_update;
  for (int i = 0; i <= n + m; i++)
  {
    last_update = false;
    // for (int i = 0; i < n + m; i++)
    //   see(i, dis[i]);
    for (int u = 0; u < n; u++)
      for (int v = 0; v < m; v++)
      {
        if (check_min(dis[n + v], dis[u] + e0[u][v]))
          last_update = true;
        if (check_min(dis[u], dis[n + v] + e1[v][u]))
          last_update = true;
      }
    if (last_update == false)
      break;
  }
  if (last_update == true)
  {
    puts("NO");
  }
  else
  {
    puts("YES");
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
      {
        if ((i + j) % 2 == 0)
          t[i][j] += dis[i] - dis[n + j];
        else
          t[i][j] += -dis[i] + dis[n + j];
        printf("%ld%c", t[i][j], " \n"[j == m - 1]);
      }
  }
}

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
    rmain();
  return 0;
}
