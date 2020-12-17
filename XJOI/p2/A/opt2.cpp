#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>
#include "/home/jack/code/creats/body.h"

/** My code begins here **/

constexpr int N = 200005;
typedef std::pair<int, long> Edge;
std::vector<Edge> e[N];
int n; std::size_t k;

void addEdge(int u, int v, long w) {
  e[u].push_back( std::make_pair(v, w) );
  e[v].push_back( std::make_pair(u, w) ); }

int vis[N], size[N];
void getSize(int u, int f) {
  size[u] = 1;
  for (auto v: e[u]) if (v.first != f && !vis[v.first]) {
    getSize(v.first, u); size[u] += size[v.first]; } }
int totSize, root, rootCost;
void getRoot(int u, int f) {
  int cost = totSize - size[u];
  for (auto v: e[u]) if (v.first != f && !vis[v.first]) {
    checkMax(cost, size[v.first]); getRoot(v.first, u); }
  if (checkMin(rootCost, cost)) { root = u; } }
bool get(int u) {
  getSize(u, 0); totSize = size[u]; 
  if (totSize == 0) { return false; }
  rootCost = std::numeric_limits<int>::max(); 
  getRoot(u, 0); return true; }

std::priority_queue<long, std::vector<long>, std::greater<long> > diss;
std::priority_queue<long> taken;
long candi[N], candi_top=0; long taken_spare[N], taken_spare_cnt=0;
void calc(int u, int f, long d) {
  candi[candi_top++] = d;
  for (auto v: e[u]) if (v.first != f && !vis[v.first]) {
    calc(v.first, u, d+v.second); } }
void dfs(int u) {
  if (get(u) == false) { return; } 
  vis[root] = true;
  while (!taken.empty()) { taken.pop(); } taken.push(0);
  for (auto v: e[root]) if (!vis[v.first]) {
    candi_top = 0;
    calc(v.first, root, v.second);
    std::sort(candi, candi+candi_top, std::greater<long>());
    for (int i=0; i<candi_top; ++i) { 
      long x = candi[i];
      while (!taken.empty()) {
        long y = taken.top(); taken_spare[taken_spare_cnt++] = y; taken.pop();
        long c = x + y; if (c <= diss.top()) { break; }
        diss.push(c); if (diss.size() > k) { diss.pop(); } }
      while (taken_spare_cnt) { taken_spare_cnt--; taken.push( taken_spare[taken_spare_cnt] ); }
    }
    for (int i=0; i<candi_top; ++i) { taken.push( candi[i] ); } }
  for (auto v: e[root]) if (!vis[v.first]) { dfs(v.first); } }

void preInit() { } void init() {
  n = sc.n(); k = sc.n();
  for (int i=0; i<n-1; ++i) { int u=sc.n(), v=sc.n(), w=sc.n(); addEdge(u,v,w); }
} void solve() {
  diss.push(-1);
  dfs(1);
  std::vector<long> ans; ans.reserve(k);
  while (!diss.empty()) { ans.push_back(diss.top()); diss.pop(); }
  std::reverse(ans.begin(), ans.end());
  for (long u: ans) { printf("%ld\n", u); }
}
