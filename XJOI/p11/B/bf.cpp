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

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 15;
int a[N], b[N], id[N];
int n;

void preInit() { } void init() {
  n = sc.n(); rep (i,n) a[i] = sc.n(); rep (i,n) b[i] = sc.n();
  rep (i,n) id[i] = i;
} void solve() {
  int ans = 0;
  do {
    rep (sta, n) {
      rep (pos, n-sta) {
        if (a[id[sta+pos]] == b[id[pos]]) {
          if (checkMax(ans, pos+1)) {
            rep (i,n) ses(a[id[i]]); see("");
            rep (i,n) ses(b[id[i]]); see("");
          } }
        else { break; } } } 
  } while (std::next_permutation(id, id+n));
  printf("%d\n", ans);
}
