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

constexpr int N = 500005;
std::vector<int> e[N];
int w[N], w2id[N];
int n, m;

void preInit() {  } 
void init() 
{
  n = sc.n(), m = sc.n();
  for (int i=1; i<=n; i++) w2id[w[i] = sc.n()] = i;
  for (int i=1; i<n; i++) { int u=sc.n(), v=sc.n(); e[u].push_back(v); e[v].push_back(u); }
} 

bool vis[N];

void solve() 
{
  int ans = 0;
  for (int r=1; r<=n; r++) {
    memset(vis, 0, sizeof(vis)); int cur = 0;
    for (int l=r; l>=1; l--) {
      cur++; int u = w2id[l]; vis[u] = true;
      for (int v: e[u]) {
        if (vis[v]) cur--; }
      if (cur <= m) { ans++; } } }
  printf("%d\n", ans);
}
