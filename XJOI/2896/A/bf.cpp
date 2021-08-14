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

constexpr int N = 10000005;
int fa[N];
int m, k;

void preInit() {  } 
void init() 
{
  m = sc.n(); k = sc.n();
} 

int get(int u) { return u == fa[u] ? u : fa[u] = get(fa[u]); }

void solve() 
{
  for (int i=0; i<m; i++) fa[i] = i;
  for (int i=0; i<m; i++) {
    int v = 1ll * i * k % m;
    fa[get(i)] = get(v); }
  int ans = 0;
  for (int i=0; i<m; i++) if (fa[i] == i) {
    ans ++; }
  printf("%d\n", ans);
}
