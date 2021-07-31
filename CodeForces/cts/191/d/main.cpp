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

constexpr int N = 300005;
std::vector<int> e[N];
int n, m;

struct circle_t : public std::vector<int> {
  int calc() const {
    if (size() == 1) { return -at(0) / 2; }
    int sum = std::accumulate(begin(), end(), 0);
    if (sum <= 1) { return 1; }
    if (std::count_if(begin(), end(), [](int x) { return x != 0; }) == 1) {
      return -(sum - 2) / 2; }
    int res = 0; for (int x: *this) res -= x / 2;
    return res; } };

std::vector<circle_t> circs;
std::stack<int> ins;
int fa[N], dfn[N], low[N], dfn_top=1;
void dfs(int u, int f) {
  dfn[u] = low[u] = dfn_top++; fa[u] = f; ins.push(u);
  for (int v: e[u]) if (v != f) {
    if (dfn[v] == 0) { dfs(v, u); }
    checkMin(low[u], low[v]); }
  if (low[u] == dfn[u]) {
    circle_t circ;
    const int sub = ins.top() == u ? 0 : 2;
    while (ins.top() != u) { 
      circ.push_back((int)e[ins.top()].size() - sub); ins.pop(); }
    circ.push_back((int)e[u].size() - sub); ins.pop(); 
    circs.emplace_back(std::move(circ)); } }

void preInit() { } 
void init() 
{
  n = sc.n(); m = sc.n();
  for (int i=0; i<m; i++) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} 

void solve() 
{
  dfs(1, 0);
  int ans = (int)circs.size() - 1;
  for (const auto& c: circs) { see(c); ans += c.calc(); }
  printf("%d %d\n", ans, m);
}
