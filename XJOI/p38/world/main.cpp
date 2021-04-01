#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/util.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 1005;
int a[N][N], n, m;

void preInit() { } void init() {
  n = sc.n(); m = sc.n();  
  rep (i,n) rep (j,m) a[i][j] = sc.nextChar() == '1';
  rep (i,n) rep (j,m) a[i][j] ^= sc.nextChar() == '1';
} void solve() {
  rep (i,n - 3) rep (j,m - 3) {
    int tmp = a[i+1][j] ^ a[i+2][j] ^ a[i][j+1] ^ a[i][j+2] ^ a[i+3][j+1] ^ a[i+3][j+2] ^ a[i+1][j+3] ^ a[i+2][j+3];
    if (tmp == 1) { puts("No"); return; } }
  puts("Yes");
}
