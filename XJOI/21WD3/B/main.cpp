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

constexpr int N = 3005;
char map[N][N];
int n, m;
int dif[N][N]; 
int pre[N][N];

void preInit() { } void init() {
  scanf("%d%d", &n, &m);
  rep (i,n) scanf("%s", map[i]);
} void solve() {
  rep (i,n-1) rep (j,m-1) dif[i][j] = map[i][j+1] == map[i+1][j];
  rep (i,n-1) rep (j,m-1) {
    if (i && dif[i-1][j] && dif[i][j]) { puts("YES"); return; }
    if (j && dif[i][j-1] && dif[i][j]) { puts("YES"); return; }
    if (i && j && pre[i-1][j-1] && dif[i][j]) { puts("YES"); return; }
    pre[i][j] = (i && pre[i-1][j]) || (j && pre[i][j-1]) || dif[i][j]; }
  puts("NO");
}
