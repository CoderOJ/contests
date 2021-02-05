// #include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

const int N = 300005;
std::vector< std::pair<int,int> > e[N];

struct Dsu {
  int p[N];
  Dsu() { rep (i,N) p[i] = i; }
  int get(int u) { return u == p[u] ? u : p[u] = get(p[u]); }
  void merge(int u, int v) { p[get(u)] = get(v); }
} st;

int n, m, k;
bool vis[3005][3005];
int cnt[N];

namespace Brute {
void dfs(int u, int v) {
  if (vis[u][v]) { return; }
  vis[u][v] = vis[v][u] = 1;
  st.merge(u, v);
  int ul=0, ur=0, vl=0, vr=0, us=e[u].size(), vs=e[v].size();
  while (ul < us) {
    int foo = e[u][ul].first;
    while (ur < us && e[u][ur].first == foo) { ur++; }
    while (vl < vs && e[v][vl].first < foo) { vl++; }
    while (vr < vs && e[v][vr].first <= foo) { vr++; }
    for (int x=ul; x<ur; x++) for (int y=vl; y<vr; y++) {
      int uu = e[u][x].second, vv = e[v][y].second;
      dfs(uu, vv); }
    ul = ur; } }
void main() {
  repa (i,n) dfs(i, i);
  repa (i,n) cnt[ st.get(i) ]++;
  long long ans = 0;
  repa (i,n) ans += 1ll * cnt[i] * (cnt[i] - 1) / 2;
  printf("%lld\n", ans);
}
} /* Brute */

void preInit() { 
#ifndef __LOCALE__
  freopen("bracket.in", "r", stdin);
  freopen("bracket.out", "w", stdout);
#endif
} void init() {
  scanf("%d%d%d", &n,&m,&k);
  rep (i,m) { int u,v,w; scanf("%d%d%d",&u,&v,&w); e[v].push_back(std::make_pair(w,u)); }
  repa (i,n) std::sort(e[i].begin(), e[i].end());
} void solve() {
  if (n <= 3000) { Brute::main(); }
}
