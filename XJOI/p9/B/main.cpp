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

#define long long long
constexpr int N = 3005;
std::vector< std::pair<int,long> >e[N];
std::vector<int> ava(1,0);
int n, m, k;

long dis[N];
long sp(long red) {
  std::priority_queue<std::pair<long,int>, std::vector<std::pair<long,int>>, std::greater<std::pair<long,int>>> que;
  memset(dis, 0x3f, sizeof(dis)); dis[1] = 0; que.push(std::make_pair(0, 1));
  while (!que.empty()) {
    int u = que.top().first; long uw = que.top().second; que.pop();
    if (uw != dis[u]) { continue; }
    for (auto p: e[u]) {
      int v = p.first; long w = std::max(0LL, p.second - red);
      if (checkMin(dis[v], uw+w)) {
        que.push(std::make_pair(dis[v], v)); } } }
  return dis[n]; }

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); k = sc.n();
  rep (i,n) {
    int u=sc.n(), v=sc.n(), w=sc.n();
    e[u].push_back( std::make_pair(v,w) );
    e[v].push_back( std::make_pair(u,w) ); }
} void solve() {
}
