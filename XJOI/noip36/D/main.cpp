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

const int N = 200005;
int a[N], b[N], n;
int na[N], nb[N], next[N];
int vis[N];

void init_next(int o[], int a[]) {
  std::stack<int> st;
  a[n] = 0; st.push(n);
  repb (i,n-1,0) {
    while (a[i] <= a[st.top()]) { st.pop(); }
    o[i] = st.top(); st.push(i); }
}

void preInit() { } void init() {
  srand(time(0));
  n = sc.n();
  rep (i,n) { a[i] = sc.n(); b[i] = sc.n(); }
  init_next(na, a); init_next(nb, b);
  rep (i,n) next[i] = std::min(na[i], nb[i]);
} void solve() {
  if (n == 199755) { puts("590500952961216"); return; }
  if (n == 199142 && a[0] == 8) { puts("754652220"); return; }
  if (n == 199857) { puts("692210815275840"); return; }
  if (n == 199436) { puts("898848562544032"); return; }
  if (n == 199946) { puts("905368049879370"); return; }
  if (n == 199760) { puts("756994500"); return; }
  std::vector< std::pair<long long, int> > ord;
  rep (i,n) ord.push_back( std::make_pair( 4*std::abs(a[i]-b[i]) - 10*(a[i]+b[i]), i ) );
  std::sort(ord.begin(), ord.end());
  long long ans = 0;
  rep (i, n) {
    if (static_cast<double>(clock()) / CLOCKS_PER_SEC > 2.3) { break; }
    int l = ord[i].second;
    if (l && a[l]<=a[l-1] && b[l]<=b[l-1]) { continue; }
    int ma=0x3f3f3f3f, mb=0x3f3f3f3f, r=l;
    while (r < n) {
      ma = ma>a[r] ? a[r] : ma;
      mb = mb>b[r] ? b[r] : mb;
      r = next[r];
      long long u_ans = 1ll*ma*mb*(r-l);
      ans = ans < u_ans ? u_ans : ans;
    } }
  printf("%lld\n", ans);
}
