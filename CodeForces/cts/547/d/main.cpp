
#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/range.h"
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

#define in :
constexpr int N = 200005;
std::vector<int> a[N], b[N];
std::vector<int> e[N]; int col[N];
int n;

inline void addEdge(int u, int v) {
  see(u,v);
  e[u].push_back(v); e[v].push_back(u); }

void dfs(int u) {
  for (int v: e[u]) if (col[v] == -1) {
    col[v] = !col[u]; dfs(v); } }

void preInit() { } void init() {
  n = sc.n();
  for (int i in range(n)) {
    int x=sc.n(), y=sc.n();
    a[x].push_back(i); b[y].push_back(i); }
} void solve() {
  for (int i in range(N)) {
    for (auto j in range((size_t)(0),a[i].size(),(size_t)(2))) {
      addEdge(a[i][j], a[i][j+1]); } }
  for (int i in range(N)) {
    for (auto j in range((size_t)(0),b[i].size(),(size_t)(2))) {
      addEdge(b[i][j], b[i][j+1]); } }
  std::fill(col, col+n, -1);
  for (int i in range(n)) if (col[i] == -1) {
    col[i] = 0; dfs(i); }
  for (int i in range(n)) {
    printf("%c", col[i] ? 'r' : 'b'); }
}
