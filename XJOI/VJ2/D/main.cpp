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

constexpr int N = 305;
constexpr int M = 2000005;
int n,m,k; 
int a[N][N], Id[N][N];
int ans[M], fa[M*2], cnt, num;
struct Que { int x,y,to,from; } q[M];

int get(int x) { return x==fa[x] ? x : fa[x]=get(fa[x]); }
void merge(int u, int v) {
  u=get(u); v=get(v); if (u==v) { return; }
  fa[u] = v; num--; }

constexpr std::pair<int,int> move[4] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
void update(int x, int y) {
  for (const auto& [dx,dy]: move) {
    if (a[x][y] == a[x+dx][y+dy]) { merge(Id[x][y], Id[x+dx][y+dy]); } } }

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); k = sc.n();
  repa (i,k) { int x=sc.n(), y=sc.n(), z=sc.n(), w=a[x][y];
    q[i] = {x,y,z,w}; a[x][y] = z; }
} void solve() {
  ans[0] = 1;
  memset(a, -1, sizeof(a)); 
  repa (i,n) repa (j,m) a[i][j]=0;
  {
    repa (i,k) { const auto& [x,y,to,from] = q[i];
      if (from == to) { continue; } num = 1;
      a[x][y] = to; Id[x][y] = ++cnt; fa[cnt] = cnt;
      update(x,y); ans[i] += num; }
  }
  memset(fa,0,sizeof(fa)); cnt=0;
  repa (i,n) repa (j,m) { Id[i][j] = ++cnt; fa[cnt]=cnt; }
  repa (i,n) repa (j,m) update(i,j);
  {
    repb (i,k,1) { const auto& [x,y,to,from] = q[i];
      if (from == to) { continue; } num = 1;
      a[x][y] = from; Id[x][y] = ++cnt; fa[cnt]=cnt;
      update(x,y); ans[i] -= num; }
  }
  repa (i,k) printf("%d\n", ans[i] += ans[i-1]);
}
