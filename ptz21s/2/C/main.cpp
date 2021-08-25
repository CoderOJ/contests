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
// #define int long long

/** My code begins here **/

constexpr int NM = 20000000;
char _p[NM], *c[NM];
char _pc[NM], *cc[NM];
int _cnt[NM], *cnt[NM];
int n, m, k;

void preInit() {  } 
void init() 
{
  n = sc.n(); m = sc.n(); k = sc.n();
  for (int i = 0; i < n + 1; i++) 
    c[i] = _p + i * (m + 1), 
    cc[i] = _pc + i * (m + 1), 
    cnt[i] = _cnt + i * (m + 1);
  for (int i = 0; i < k; i++)
  {
    int x = sc.n() - 1, y = sc.n() - 1;
    c[x][y] = 1;
  }
} 

constexpr int mv[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
void dfs(char **c, int x, int y, char goal)
{
  // see(x, y);
  if (x < 0 || y < 0 || x >= n || y >= m || c[x][y] != goal) return; 
  c[x][y] = -1;
  for (const auto [dx,dy] : mv) dfs(c, x + dx, y + dy, goal);
}

bool global_connected(char **c, char goal)
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (c[i][j] == goal)
      {
        dfs(c, i, j, goal);
        goto out;
      }
out:;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (c[i][j] == goal)
      {
        // see(i, j, goal);
        return false;
      }
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (c[i][j] == -1) 
        c[i][j] = goal;
  return true;
}

int xc[NM];
bool check(int k)
{
  // see(k);
  memset(_cnt, 0, sizeof(_cnt));
  memset(_pc, 0, sizeof(_pc));
  if (k == 0) return true;
  memset(xc, 0, sizeof(xc));
  for (int i = 0; i < k; i++)
    for (int j = 0; j < m; j++)
      xc[j] += c[i][j];
  for (int i = k; i <= n; i++)
  {
    int last_zero = 0; 
    for (int j = 0; j < m; j++)
    {
      if (xc[j]) last_zero = j + 1;
      if (j - last_zero + 1 >= k)
      {
        // see(i-1, j);
        cc[i-1][j] = 1;
        cnt[i][j+1]++;
        cnt[i - k][j+1]--;
        cnt[i][j+1 - k]--;
        cnt[i - k][j+1 - k]++;
      }
    }
    for (int j = 0; j < m; j++)
      xc[j] += c[i][j] - c[i - k][j];
  }
  for (int i = 0; i + 1 < n; i++)
    for (int j = 0; j < m; j++)
      cnt[i + 1][j] += cnt[i][j];
  for (int i = 0; i < n; i++)
    for (int j = 0; j + 1 < m; j++)
      cnt[i][j + 1] += cnt[i][j];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (c[i][j] == 0 && cnt[i][j] == 0)
        return false;
  if (!global_connected(cc, 1)) 
    return false;
  return true;
}

void solve() 
{
  if (!global_connected(c, 0)) { puts("-1"); return; }
  int l = 1, r = std::min(n, m);
  while (l < r) 
  {
    int mid = (l + r + 1) / 2;
    if (check(mid)) { l = mid; }
    else { r = mid - 1; }
  }
  std::cout << l << std::endl;
}
