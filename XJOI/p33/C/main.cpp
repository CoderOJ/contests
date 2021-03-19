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
#define int long long

/** My code begins here **/

constexpr int N = 1000005;
int a[N], b[N], n, type;

void preInit() { } void init() {
  n = sc.n(); type = sc.n();
  rep (i,n-1) a[i] = sc.n();
  rep (i,n-1) b[i] = sc.n();
} void solve() {
  if (type == 1) { puts("bukejiedewodeyiqie"); return; }
  if (n % 2 == 1) { puts("bukejiedewodeyiqie"); return;  }
  {
    int last = 0;
    printf("%lld", last);
    rep (i,n-1) { last = a[i] - last; printf(" %lld\n",last); }
  }
  {
    int last = 0;
    printf("%lld", last);
    rep (i,n-1) { last = b[i] - last; printf(" %lld\n",last); }
  }
}
