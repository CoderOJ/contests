#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>
#include "/home/jack/code/creats/body.h"

/** My code begins here **/

constexpr int N = 500005;
constexpr int B = 20;
int a[N], n;
int rp[N], ph[N];

struct STable {
  int a[N], min[B][N], max[B][N];
  int log[N];
  inline int cmp_min(int x, int y) { return a[x]!=a[y] ? (a[x]<a[y] ? x : y) : (x<y ? x : y); }
  inline int cmp_max(int x, int y) { return a[x]!=a[y] ? (a[x]>a[y] ? x : y) : (x<y ? x : y); }
  void init(int _a[], int n) {
    log[1] = 0; repi (i,2,n) log[i] = log[i / 2] + 1;
    memcpy(a, _a, sizeof(*a) * n);
    rep (i,n) min[0][i] = max[0][i] = i;
    rep (b, B-1) { int step = 1 << b, end = n - step;
      rep (i,end) { max[b+1][i] = cmp_max(max[b][i], max[b][i+step]);
                    min[b+1][i] = cmp_min(min[b][i], min[b][i+step]); } } }
  int queryMin(int l, int r) {
    int _log = log[r - l + 1], _pow = 1 << _log; 
    return cmp_min(min[_log][l], min[_log][r - _pow + 1]); }
  int queryMax(int l, int r) {
    int _log = log[r - l + 1], _pow = 1 << _log; 
    return cmp_max(max[_log][l], max[_log][r - _pow + 1]); }
} sta, stp;

void preInit() { } void init() {
  n = sc.n(); rep (i,n) a[i + 1] = a[i] + (sc.nextChar() == 'C' ? 1 : -1);
  sta.init(a, n + 1);
  std::stack< std::pair<int, int> > st; st.push(std::make_pair(-N, n+1));
  repb (i,n,0) {
    while (st.top().first >= a[i]) { st.pop(); }
    rp[i] = st.top().second - 1;
    st.push(std::make_pair(a[i], i)); }
  rep (i,n+1) ph[i] = a[sta.queryMax(i, rp[i])] - a[i];
  stp.init(ph, n+1);
} void solve() {
  int q = sc.n(); while (q--) {
    int l = sc.n()-1, r = sc.n();
    int min_id = sta.queryMin(l, r);
    int ans1 = a[l] - a[min_id];
    int top = a[sta.queryMax(min_id, r)] - a[min_id];
    if (min_id != l) { checkMax(top, ph[stp.queryMax(l, min_id - 1)]); }
    int ans2 = top - (a[r] + ans1 - a[l]);
    // see(min_id, ans1, ans2, top);
    printf("%d\n", ans1 + ans2);
  }
}
