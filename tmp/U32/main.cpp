#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
#define int long long

/** My code begins here **/

int idivflq(int a, int b)
{
	if (b < 0) a = -a, b = -b;
	return a >= 0 ? a / b : a / b - (a % b != 0);
}

int idivceq(int a, int b)
{
  return -idivflq(-a, b);
}

constexpr int N = 105;
constexpr int INF = 0x3f3f3f3f3f3f3f3f;
struct edge_t { int v, w, z; };
std::vector<edge_t> e[N];
bool eb[N][N];
int n, m;

void preInit() { } 
void init() 
{
  n = sc.n(); m = sc.n();
  for (int i = 0; i < m; i++)
  {
    int u = sc.n(), v = sc.n(), w = sc.nextInt(), z = sc.nextInt();
    e[u].push_back({v, w, z});
    eb[u][v] = true;
  }
} 

int f[N][N][N * 2];
std::vector<std::pair<int,int>> inters[N];
void solve() 
{
  for (int r = 1; r <= n; r++)
    for (int u = 1; u <= n; u++)
      for (int v = 1; v <= n; v++)
        eb[u][v] |= eb[u][r] && eb[r][v];

  memset(f, 0x3f, sizeof(f));
  for (int i = 0; i <= n; i++)
    f[i][1][n] = 0;
  for (int t = 0; t < n; t++)
    for (int u = 1; u <= n; u++)
      for (int i = n - t; i <= n + t; i++)
        if (f[t][u][i] < INF)
          for (const auto& [v,w,z] : e[u])
            checkMin(f[t + 1][v][i + z], f[t][u][i] + w);

  for (int i = 1; i <= n; i++)
    for (int k = 0; k <= 2*n; k++)
      if (f[n][i][k] < INF)
      {
        int l = -INF, r = INF;
        for (int j = 0; j <= 2*n; j++)
          if (f[n][i][j] < INF)
          {
            if (j < k) checkMin(r, idivceq(f[n-1][i][j] - f[n][i][k], k - j));
            else if (j > k) checkMax(l, idivflq(f[n-1][i][j] - f[n][i][k], k - j));
            else if (f[n][i][k] >= f[n-1][i][j]) { l=INF, r=-INF; }
          }
        if (l < r)
          inters[i].emplace_back(l, r);
      }

  for (int i = 1; i <= n; i++)
  {
    std::vector<std::pair<int,int>> s;
    for (int j = 1; j <= n; j++)
      if (eb[1][j] && eb[j][i])
        for (const auto& x: inters[j]) 
          s.push_back(x);

    int l = INF, r = -INF;
    for (const auto& [cl,cr] : s)
    {
      checkMin(l, cl);
      checkMax(r, cr);
    }

    if (l > -INF || r < INF) 
      puts("-1");
    else
    {
      std::sort(s.begin(), s.end());
      int cur = -INF; l = 1, r = 0;
      for (const auto& [cl,cr] : s)
      {
        if (cur != -INF && cl >= cur) { l = cur; r = cl; break; }
        checkMax(cur, cr);
      }
      printf("%lld\n", l <= r ? r - l + 1 : 0ll);
    }
  }
}
