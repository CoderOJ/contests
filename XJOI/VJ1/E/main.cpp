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

constexpr int N = 105;
constexpr int K = 10000005;
int a[K], n, MAX;
bool del[K], vis[K];
std::vector<int> odd, even, pri;

int last[K], to[N*N], next[N*N], e_cnt;
int match[K];

bool dfs(int u) {
  for (int i=last[u]; i!=-1; i=next[i]) {
    if (!vis[to[i]]) {
      vis[to[i]] = true;
      if (!match[to[i]] || dfs(match[to[i]])) {
        match[to[i]] = u; return true; } } }
  return false; }

void preInit() { } void init() {
  memset(next, -1, sizeof(next));
  memset(last, -1, sizeof(last));
  n = sc.n();
  rep (i,n) {
    int x = sc.n(); a[x] = true; checkMax(MAX, x+1); }
} void solve() {
  repb (i,MAX,1) { a[i] ^= a[i-1]; }
  repa (i,MAX) if (a[i]) { 
    ((i % 2) ? odd : even).push_back(i); } 

  del[1] = true;
  repi (i,2,MAX) {
    if (!del[i]) { pri.push_back(i); }
    for (int j: pri) {
      if (1ll * j * i > MAX) { break; }
      del[i * j] = true;
      if (i % j == 0) { break; } } }
  
  see(del[9]);
  for (int i: odd) for (int j: even) {
    if (!del[std::abs(j - i)]) {
      to[e_cnt] = j; next[e_cnt] = last[i]; last[i] = e_cnt++; } }

  int ans = 0;
  for (int i: odd) if (!match[i]) {
    for (int j: even) vis[j] = false;
    ans += dfs(i); }
  int ans2 = ans + ((int)(odd.size())-ans) /2*2 + ((int)(even.size())-ans) /2*2;
  see(ans, ans2);
  printf("%d\n", ans2 + (((int)(odd.size()) - ans) % 2) * 3);
}
