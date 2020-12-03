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

const int N = 1000005;
std::vector<int> e[N];
int col[N], vis[N], n, m, ans;
char s[N];

std::set<int> anc;
void dfs(int u) {
  anc.insert(u); vis[u] = 1;
  for (int v: e[u]) {
    if (vis[v]) { ans |= (anc.count(v)); }
    else { dfs(v); } }
  anc.erase(u); }

void preInit() { } void init() {
  scanf("%d%d%s", &n,&m,s);
  rep (i,n) col[i+1] = s[i]=='B';
} void solve() {
  rep (i,m) { 
    int u,v; scanf("%d%d",&u,&v);
    if (col[u] == col[v]) { e[u].push_back(v+n); e[v].push_back(u+n); }
    else { e[u+n].push_back(v); e[v+n].push_back(u); } }
  repa (i,2*n) if (!vis[i]) { dfs(i); }
  puts(ans ? "Yes" : "No");
}
