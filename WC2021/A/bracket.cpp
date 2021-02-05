#ifndef LOOP_H_
#define LOOP_H_ 1

#define repe(a, b) for (int a = 0; a < (int)b.size(); a++)
#define rep(i, n) for (int i = 0; i < n; i++)
#define repa(i, n) for (int i = 1; i <= n; i++)
#define repi(i, a, b) for (int i = a; i <= b; i++)
#define repb(i, a, b) for (int i = a; i >= b; i--)

#endif /* LOOP_H_ */

#include <bits/stdc++.h>

const int N = 3005;
std::vector< std::pair<int,int> > e[N];

int n, m, k;
int cnt[N];

namespace Brute {
std::vector< std::pair<int,int> > links[4501505];
int encode(int u, int v) { 
  if (u < v) { std::swap(u, v); }
  return u * (u-1) / 2 + v; }

struct Dsu {
  std::vector<int> st[N];
  int p[N];
  Dsu() { rep (i,N) { p[i] = i; st[i].push_back(i); } }
  int get(int u) { return u == p[u] ? u : p[u] = get(p[u]); }
  void merge(int u, int v) { 
    u = get(u); v = get(v);
    std::vector< std::pair<int,int> > mergeList;
    if (u != v) {
      if (st[u].size() < st[v].size()) { std::swap(u, v); }
      p[v] = u;
      for (std::vector<int>::iterator it=st[v].begin(); it!=st[v].end(); ++it) {
        for (std::vector<int>::iterator ut=st[u].begin(); ut!=st[u].end(); ++ut) {
          int uu = *ut, vv = *it, code = encode(uu, vv);
          for (std::vector<std::pair<int,int> >::iterator ct = links[code].begin(); ct != links[code].end(); ++ct) {
            mergeList.push_back(*ct); } } }
      for (std::vector<int>::iterator it=st[v].begin(); it!=st[v].end(); ++it) {
        st[u].push_back(*it); }
      for (std::vector<std::pair<int, int> >::iterator it = mergeList.begin(); it != mergeList.end(); ++it) {
        merge(it->first, it->second); } } }
} st;

void dfs(int u, int v) {
  int ul=0, ur=0, vl=0, vr=0, us=e[u].size(), vs=e[v].size();
  while (ul < us) {
    int foo = e[u][ul].first;
    while (ur < us && e[u][ur].first == foo) { ur++; }
    while (vl < vs && e[v][vl].first < foo) { vl++; }
    while (vr < vs && e[v][vr].first <= foo) { vr++; }
    for (int x=ul; x<ur; x++) for (int y=vl; y<vr; y++) {
      int uu = e[u][x].second, vv = e[v][y].second;
      links[encode(u,v)].push_back(std::make_pair(uu, vv)); }
    ul = ur; } }
void main() {
  repa (i,n) repi (j,i,n) dfs(i,j);
  repa (i,n) { int code = encode(i,i);
    for (std::vector<std::pair<int, int> >::iterator it = links[code].begin(); it != links[code].end(); ++it) {
      st.merge(it->first, it->second); } }
  repa (i,n) cnt[st.get(i)]++;
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

int main() { preInit(); init(); solve(); return 0; }
