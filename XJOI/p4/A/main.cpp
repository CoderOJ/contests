#include "/home/jack/code/creats/gpl.h"

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

#define long long long
constexpr int N = 200005;
constexpr long INF = 0x3f3f3f3f3f3f3f3f;
char map[2][N];
long dis1[2][N], dis2[2][N];
int n, q;

void getDis(long dis[][N], int first, int second) {
  rep (i,n) { 
    if (map[first][i] == '0') dis[first][i] = i*5*N; else dis[first][i] = INF;
    if (map[second][i] == '0') dis[second][i] = i*5*N+1; else dis[second][i] = INF; }
  rep (i,n) {
    if (i) {
      if (map[0][i-1] == '0' && map[0][i] == '0') { checkMin(dis[0][i], dis[0][i-1]+1); }
      if (map[1][i-1] == '0' && map[1][i] == '0') { checkMin(dis[1][i], dis[1][i-1]+1); } }
    if (map[0][i] == '0' && map[1][i] == '0') { 
      checkMin(dis[1][i], dis[0][i]+1); checkMin(dis[0][i], dis[1][i]+1); }
    if (map[0][i] == '1') { dis[0][i] = INF; }
    if (map[1][i] == '1') { dis[1][i] = INF; } }
}

void preInit() { } void init() {
  scanf("%d%d", &n, &q);
  scanf("%s%s", map[0], map[1]);
} void solve() {
  getDis(dis1, 0, 1);
  getDis(dis2, 1, 0);
  rep (i,q) {
    int u,v; scanf("%d%d", &u, &v); u--; v--;
    int ux=u/n, uy=u%n, vx=v/n, vy=v%n;
    if (uy > vy) { std::swap(ux,vx); std::swap(uy,vy); }
    long udis, vdis;
    if (ux == 0) { udis = dis1[ux][uy]; vdis = dis1[vx][vy]; }
    else         { udis = dis2[ux][uy]; vdis = dis2[vx][vy]; }
    see(ux,uy,vx,vy);
    long delta = std::abs(vdis - udis); 
    if ((map[ux][uy] == '1' || map[vx][vy] == '1') || delta >= n*2) { puts("You have been confusional!"); }
    else { printf("%lld\n", delta); } }
}
