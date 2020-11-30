#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/


void preInit()
{

}

const int N = 10;
int n,m;
int a[N][N];

const int bar[14][4][2] = 
{
  { {0,0}, {0,1}, {0,2}, {0,3} }, 
  { {0,0}, {1,0}, {2,0}, {3,0} }, 

  { {0,0}, {0,1}, {0,2}, {1,1} }, 
  { {0,0}, {1,0}, {2,0}, {1,1} }, 

  { {1,0}, {1,1}, {1,2}, {0,0} },
  { {0,1}, {1,1}, {2,1}, {0,0} },
  { {0,0}, {0,1}, {0,2}, {1,0} },
  { {0,0}, {1,0}, {2,0}, {0,1} },
  { {0,0}, {0,1}, {0,2}, {1,2} },
  { {0,0}, {1,0}, {2,0}, {2,1} },

  { {0,1}, {1,0}, {1,1}, {1,2} }, 
  { {1,0}, {0,1}, {1,1}, {2,1} },
  { {1,0}, {1,1}, {1,2}, {0,2} },
  { {0,1}, {1,1}, {2,1}, {2,0} }

};

void init()
{
  n = sc.n(); m = sc.n();
  rep (i,n) rep (j,m) a[i][j] = sc.nextChar() == '*';
}

inline bool valid_single(const int x, const int y) { 
  return x<n && y<m && !a[x][y]; }

inline bool valid_group(const int id, const int base_x, const int base_y) {
  return valid_single(base_x + bar[id][0][0], base_y + bar[id][0][1]) && 
         valid_single(base_x + bar[id][1][0], base_y + bar[id][1][1]) && 
         valid_single(base_x + bar[id][2][0], base_y + bar[id][2][1]) && 
         valid_single(base_x + bar[id][3][0], base_y + bar[id][3][1]); }

inline void set_group(const int id, const int base_x, const int base_y) {
  a[base_x + bar[id][0][0]][base_y + bar[id][0][1]] = 1; 
  a[base_x + bar[id][1][0]][base_y + bar[id][1][1]] = 1; 
  a[base_x + bar[id][2][0]][base_y + bar[id][2][1]] = 1; 
  a[base_x + bar[id][3][0]][base_y + bar[id][3][1]] = 1; }

inline void free_group(const int id, const int base_x, const int base_y) {
  a[base_x + bar[id][0][0]][base_y + bar[id][0][1]] = 0; 
  a[base_x + bar[id][1][0]][base_y + bar[id][1][1]] = 0; 
  a[base_x + bar[id][2][0]][base_y + bar[id][2][1]] = 0; 
  a[base_x + bar[id][3][0]][base_y + bar[id][3][1]] = 0; }

int ans = 0;
void dfs(int id) {
  if (id == n * m) { ans++; }
  int pos_x = id / m, pos_y = id % m;
  if (a[pos_x][pos_y] == 1) { 
    dfs(id+1); 
    repi (i,10,13) { 
      if (valid_group(i, pos_x, pos_y)) {
        set_group(i, pos_x, pos_y);
        dfs(id+1);
        free_group(i, pos_x, pos_y); } } }
  else {
    rep (i,10) {
      if (valid_group(i, pos_x, pos_y)) {
        set_group(i, pos_x, pos_y);
        dfs(id+1);
        free_group(i, pos_x, pos_y); } } }
}

void solve()
{
  dfs(0);
  printf("%d\n", ans);
}
