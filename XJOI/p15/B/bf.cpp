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

constexpr int N = 100005;
std::set<int> e[N];
int n, q;

bool isConnect(int u, int g, int f=0) {
  if (u == g) { return 1; }
  for (int v: e[u]) if (v != f) {
    if (isConnect(v,g,u)) { return 1; } }
  return 0; }

bool visited;
int dfs(int u, int g, int f=0) {
  if (u == g) { visited = 1; return 1; }
  int res = 1;
  for (int v: e[u]) if (v != f) { res += dfs(v,g,u); }
  return res; }

void preInit() { } void init() {
  n = sc.n(); q = sc.n();
} void solve() {
  while (q--) {
    int opt = sc.n(), u=sc.n(), v=sc.n();
    if (opt == 0) {
      bool visibility = isConnect(u,v);
      if (visibility) { puts("ILLEGAL"); }
      else { puts("OK"); e[u].insert(v); e[v].insert(u); } }
    else if (opt == 1) {
      if (e[u].count(v)) { e[u].erase(v); e[v].erase(u); puts("OK"); }
      else { puts("ILLEGAL"); } }
    else { 
      visited = false; int ans = dfs(u,v)-1;
      if (visited) { printf("%d.0000\n", ans); } 
      else { puts("ILLEGAL"); } } }
}
