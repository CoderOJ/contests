#include <bits/stdc++.h>

#define rep(i,n) for (int i=0;i<n;++i)
#define repa(i,n) for (int i=1;i<=n;++i)

#define int long long

constexpr int N = 200005;

int n, m;
int h[N], d[N];

struct STree {
  struct Node {
    int l, r;
    int lg, rg, ans;
    void pushUp(const Node& a, const Node& b) {
      l = a.l; r = b.r;
      lg = std::max(a.lg, b.lg + d[b.l] - d[l]);
      rg = std::max(a.rg + d[r] - d[a.r], b.rg);
      ans = std::max(std::max(a.ans, b.ans), a.rg + b.lg + d[b.l] - d[a.r]); }
  } p[N * 4];
  static constexpr int root = 1;

  void init(int l, int r, int u = root) {
    if (l == r) {
      p[u].l = p[u].r = l; p[u].ans = 0;
      p[u].lg = p[u].rg = h[l] * 2; }
    else {
      int mid = (l + r) / 2;
      init(l, mid, u+u); init(mid+1, r, u+u+1);
      p[u].pushUp(p[u+u], p[u+u+1]); } }
  Node query(int sl, int sr, int l, int r, int u = root) {
    if (sl <= l && r <= sr) { return p[u]; }
    int mid = (l + r) / 2;
    if (sl > mid) { return query(sl, sr, mid+1, r, u+u+1); }
    if (sr <= mid) { return query(sl, sr, l, mid, u+u); }
    Node ans; ans.pushUp(query(sl, sr, l, mid, u+u), query(sl, sr, mid+1, r, u+u+1));
    return ans; }
} ST;

signed main() {
  scanf("%lld%lld", &n, &m);
  repa (i,n) scanf("%lld", &d[i]); memcpy(d+n+1, d+1, sizeof(*d) * n);
  repa (i,n*2) d[i] += d[i-1];
  rep (i,n) scanf("%lld", &h[i]); memcpy(h+n, h, sizeof(*h) * n);
  int s_n = n * 2 - 1;
  ST.init(0, s_n);

  while (m--) {
    int l, r; scanf("%lld%lld", &l, &r); l--; r--;
    STree::Node ans;

    if (l <= r) { ans = ST.query(r+1, n+l-1, 0, s_n); }
    else { ans = ST.query(r+1, l-1, 0, s_n); }
    
    printf("%lld\n", ans.ans);
  }

  return 0;
}
