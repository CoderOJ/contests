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

constexpr int N = 50;
char s[N][N];
int n, m;

void preInit() {  } 
void init() 
{
  n = sc.n(); m = sc.n();
  for (int i=0; i<n; i++) sc.next(s[i]);
} 

int col[N][N];
void dfs(int x, int y, int c) {
  static constexpr int det[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};
  if (s[x][y] != '#') return;
  if (col[x][y] != -1) return; col[x][y] = c;
  for (const auto& [dx,dy]: det) {
    int vx = dx + x, vy = dy + y;
    if (vx >= 0 && vx < n && vy >= 0 && vy < m)
      dfs(vx, vy, c); } }
bool check() {
  memset(col, -1, sizeof(col)); int c = 1;
  for (int i=0; i<n; i++) for (int j=0; j<m; j++) {
    if (s[i][j] == '#' && col[i][j] == -1) dfs(i, j, c++); }
  return c >= 3; }

void solve() 
{
  if (check()) { puts("0"); return; } int cnt = 0;
  for (int i=0; i<n; i++) for (int j=0; j<m; j++) if (s[i][j] == '#') { cnt++;
    s[i][j] = '.'; if (check()) { puts("1"); return; } s[i][j] = '#'; }
  puts(cnt <= 2 ? "-1" : "2");
}
