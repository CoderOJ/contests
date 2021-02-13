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

constexpr int N = 200005;
#define int long long
int a[N], b[N], n;
int l[N], r[N];
bool vis[N];

inline int dis(int i, int j) {
  return std::abs(a[i] - b[j]); }
inline bool check(int i) {
  return dis(l[i],i) > dis(i,i) && dis(r[i], i) >= dis(i, i); }

void preInit() { } void init() {
  n = sc.n();
  repa (i,n) { a[i] = sc.n(); } std::sort(a+1, a+n+1);
  repa (i,n) { b[i] = sc.n(); } std::sort(b+1, b+n+1);
  repa (i,n) l[i] = i - 1;
  repa (i,n) r[i] = i + 1;
  a[0] = -1e10; a[n+1] = 1e10;
} void solve() {
  int ans = 0;
  repa (i,n) { ans += std::abs(a[i] - b[i]); }
  printf("%lld\n", ans);

  std::queue<int> que;
  repa (i,n) vis[i] = 1;
  repa (i,n) if (check(i)) { que.push(i); }

  while (!que.empty()) {
    int u = que.front(); que.pop(); 
    if (!vis[u]) { continue; } vis[u] = false;
    printf("%lld ", u);
    int ll = l[u], rr = r[u];
    r[ll] = rr; l[rr] = ll;
    if (vis[ll] && check(ll)) { que.push(ll); }
    if (vis[rr] && check(rr)) { que.push(rr); } }
}
