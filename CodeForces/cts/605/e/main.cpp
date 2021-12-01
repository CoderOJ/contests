#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 1005, 1005)
double p[N][N];
double dis[N], prob[N];
bool   vis[N];
int    n;

int main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      p[i][j] = sc.next_int() / 100.0;

  prob[n - 1] = 1;
  for (int r = 0; r < n; r++)
  {
    // see(r);
    // see(std::vector(vis, vis + n));
    // see(std::vector(dis, dis + n));
    // see(std::vector(prob, prob + n));

    double min_dis = 1e100;
    int min_u = -1;
    for (int u = 0; u < n; u++)
      if (!vis[u] && prob[u] != 0 && check_min(min_dis, (dis[u] + 1 - prob[u]) / prob[u]))
        min_u = u; 
    dis[min_u] = (dis[min_u] + 1 - prob[min_u]) / prob[min_u];

    vis[min_u] = true;
    for (int u = 0; u < n; u++)
      if (!vis[u])
      {
        dis[u] += (1 - prob[u]) * p[u][min_u] * (dis[min_u] + 1);
        prob[u] = 1 - (1 - prob[u]) * (1 - p[u][min_u]);
      }
  }

  printf("%.15lf\n", dis[0]);

  return 0;
}
