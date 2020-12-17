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
void getSize(int u, int f) noexcept {
  size[u] = 1;
  for (auto v: e[u]) if (v.first != f && !vis[v.first]) {
    getSize(v.first, u); size[u] += size[v.first]; } }
int totSize, root, rootCost;
void getRoot(int u, int f) noexcept {
  int cost = totSize - size[u];
  for (auto v: e[u]) if (v.first != f && !vis[v.first]) {
    checkMax(cost, size[v.first]); getRoot(v.first, u); }
  if (checkMin(rootCost, cost)) { root = u; } }
bool get(int u) noexcept {
  getSize(u, 0); totSize = size[u]; 
  if (totSize == 0) { return false; }
  rootCost = std::numeric_limits<int>::max(); 
  getRoot(u, 0); return true; }

long thr; std::vector<long> diss;
std::multiset < long, std::greater<long> > taken; 
std::vector<long> candi;
struct ExceptionFinish {}; 
void calc(int u, int f, long d) {
  candi.push_back(d);
  for (long pre: taken) {
    if (pre + d < thr) { break; }
    if (diss.size() == k) { throw ExceptionFinish(); } 
    diss.push_back(pre + d); }
  for (auto v: e[u]) if (v.first != f && !vis[v.first]) {
    calc(v.first, u, d+v.second); } }
void dfs(int u) {
  if (get(u) == false) { return; } 
  vis[root] = true;
  taken.clear(); taken.insert(0);
  for (auto v: e[root]) if (!vis[v.first]) {
    candi.clear(); candi.reserve(size[v.first]);
    calc(v.first, root, v.second);
    for (long d: candi) { taken.insert(d); } }
  for (auto v: e[root]) if (!vis[v.first]) { dfs(v.first); } }

bool valid(long _thr) noexcept {
  memset(vis, 0, sizeof(vis));
  thr = _thr; diss.clear(); diss.reserve(k);
  try { dfs(1); } 
  catch (...) { return false; }
  return true;
}

void preInit() { } void init() {
  n = sc.n(); k = sc.n();
  for (int i=0; i<n-1; ++i) { int u=sc.n(), v=sc.n(), w=sc.n(); addEdge(u,v,w); }
} void solve() {
  long l = 1, r = 1e15;
  while (l < r) {
    long mid = (l+r) / 2;
    if (valid(mid)) { r = mid; }
    else { l = mid + 1; } }
  valid(l);
  std::sort(diss.begin(), diss.end(), std::greater<long>());
  std::size_t cnt = k;
  for (long u: diss) { printf("%ld\n", u); cnt--; }
  while (cnt) { printf("%ld\n", l-1); cnt--; }
}
