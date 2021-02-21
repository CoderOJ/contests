
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

constexpr int N = 50;
int a[N], n;

void preInit() { } void init() {
  n = sc.n(); rep (i,n) a[i] = sc.n();
} void solve() {
  int ans = 0;
  rep (b,(1<<n)) if(b) {
    std::vector<int> pos;
    rep (i,n) if (b & (1<<i)) pos.push_back(a[i]);
    std::sort(pos.begin(), pos.end());
    ans += pos[pos.size() / 2] == pos[(pos.size()-1) / 2]; }
  printf("%d\n", ans);
}
