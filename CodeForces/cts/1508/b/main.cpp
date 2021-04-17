#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
#define int long long

/** My code begins here **/

constexpr int N = 100005;
int n, k;
int ans[N];

bool comp(int len, int k) {
  if (len >= 62) { return false; }
  return (1ll << std::max(0ll,len)) < k;
}

void preInit() { } void init() {
  n = sc.n(); k = sc.nl();
} void solve() {
  int pos = 1;
  while (pos <= n) {
    int tmp = pos;
    for (; tmp<=n; ++tmp) {
      if (comp(n - tmp - 1, k)) {
        k -= 1ll << std::max(n-tmp-1, 0ll); }
      else { break; } }
    see(pos, tmp);
    if (tmp > n) { puts("-1"); return; }
    int cnt = tmp - pos + 1;
    for (int i=0; i<cnt; ++i) { ans[pos++] = tmp - i; }
  }
  if (k > 1) { puts("-1"); }
  else { for (int i=1; i<=n; ++i ) printf("%lld%c", ans[i], " \n"[i==n]); }
}
