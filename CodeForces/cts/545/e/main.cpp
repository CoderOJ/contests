#include "/home/jack/code/creats/gpl.h"

#define SCANNER_H_CUSTOM
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
#define int long long

/** My code begins here **/

constexpr int N = 300005;
std::vector<std::tuple<int,int,int>> e[N];
int dis[N], w[N], pre[N], n, m, u;

void preInit() { } void init() {
  Scanner sc(stdin);
  n = sc.n(); m = sc.n();
  repa (i,m) { int u=sc.n(), v=sc.n(), w=sc.n(); e[u].push_back({v,w,i}); e[v].push_back({u,w,i}); ::w[i] = w; }
  u = sc.n();
} void solve() {
  std::fill(dis+1, dis+n+1, std::numeric_limits<int>::max()); dis[u] = 0; 
  std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> que; que.push({0,u});
  while (!que.empty()) {
    const auto [uw,u] = que.top(); que.pop();
    see(u, uw);
    if (dis[u] != uw) { continue; }
    for (const auto& [v,vw,vi]: e[u]) {
      if (checkMin(dis[v], uw+vw)) { see(v,vw,vi); que.push({dis[v],v}); pre[v] = vi; }
      else if (dis[v] == uw+vw) { pre[v] = vi; } } }
  int ans = 0; std::vector<int> aids;
  repa (i,n) if (i != u) { see(i,pre[i]); aids.push_back(pre[i]); ans += w[pre[i]]; }
  printf("%lld\n", ans);
  std::sort(aids.begin(), aids.end());
  std::ostream_iterator<int> out(std::cout, " ");
  std::copy(aids.begin(), aids.end(), out);
}
