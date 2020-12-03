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

const int N = 1000005;
std::vector<int> e0[N], e1[N], e[N];
int col[N], vis[N], n, m, ans;
int cnt;

void dfs(int u, int id) {
  cnt++;
  vis[u] = 1;
  for (int v: e[u]) {
    if (vis[v]) { ans |= (v == id); }
    else { dfs(v,id); } } }

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); repa (i,n) col[i] = sc.nextChar() == 'B'; 
} void solve() {
  rep (i,m) { 
    int u=sc.n(), v=sc.n();
    if (col[u] == col[v]) { e0[u].push_back(v); e0[v].push_back(u); }
    else { e1[u].push_back(v); e1[v].push_back(u); } }
  repa (i,n) for (int u:e0[i]) for (int v:e1[i]) { e[u].push_back(v); }
  repa (i,n) { memset(vis, 0, sizeof(vis)); dfs(i,i); }
  puts(ans ? "Yes" : "No");
  fprintf(stderr, ans ? "Yes\n" : "No\n");
  see(cnt);
}
