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

constexpr int N = 500005;

struct STree {
  struct Node {
    int val, add, ass, str, stt;
    Node () { val=0; add=0; ass=-1; str=0; stt=0; }
    void pushAdd(int del) { val += del; add += del; }
    void pushStr(int del) { str += del; stt += del; }
    void pushAss(int del); 
    void pushDown(Node& a, Node& b) {
      if (ass != -1) { a.pushAss(ass); b.pushAss(ass); } ass = -1;
      if (add != 0) { a.pushAdd(add); b.pushAdd(add); } add = 0; 
      if (stt != 0) { a.pushStr(stt); b.pushStr(stt); } stt = 0; }
  };

  Node p[N*4];
  static constexpr int root = 1;
  void build(int a[], int l, int r, int u = root) {
    if (l == r) { p[u].val = a[l]; return; }
    int mid = (l + r) / 2;
    build(a, l, mid, u+u); build(a, mid+1, r, u+u+1); }
  void add(int sl, int sr, int l, int r, int del, int u = root) {
    if (sl <= l && r <= sr) { p[u].pushAdd(del); return; }
    p[u].pushDown(p[u+u], p[u+u+1]);
    int mid = (l + r) / 2;
    if (sl <= mid) add(sl, sr, l, mid, del, u+u);
    if (sr > mid) add(sl, sr, mid+1, r, del, u+u+1); }
  void ass(int sl, int sr, int l, int r, int del, int u = root) {
    if (sl <= l && r <= sr) { p[u].pushAss(del); return; }
    p[u].pushDown(p[u+u], p[u+u+1]);
    int mid = (l + r) / 2;
    if (sl <= mid) ass(sl, sr, l, mid, del, u+u);
    if (sr > mid) ass(sl, sr, mid+1, r, del, u+u+1); }
  void str(int sl, int sr, int l, int r, int del, int u = root) {
    if (sl <= l && r <= sr) { p[u].pushStr(del); return; }
    p[u].pushDown(p[u+u], p[u+u+1]);
    int mid = (l + r) / 2;
    if (sl <= mid) str(sl, sr, l, mid, del, u+u);
    if (sr > mid) str(sl, sr, mid+1, r, del, u+u+1); }
  int query(int pos, int l, int r, int u = root) {
    if (l == r) { return ((p[u].val + p[u].str % 26 * pos) % 26 + 26) % 26; }
    p[u].pushDown(p[u+u], p[u+u+1]);
    int mid = (l + r) / 2;
    if (pos <= mid) { return query(pos, l, mid, u+u); }
    else { return query(pos, mid+1, r, u+u+1); } }
} ST;

void STree::Node::pushAss(int del) { val = ass = del; add = 0; str = stt = 0; }

int a[N], n, m;

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,n) a[i] = sc.nextChar() - 'A';
  ST.build(a, 0, n-1);
} void solve() {
  int stp = 0;
  while (m--) {
    int opt = sc.n();
    if (opt == 1) {
      int l=sc.n(), r=sc.n(), c=sc.nextChar() - 'A'; l += stp-1; r += stp-1;
      if (r < n) { ST.ass(l, r, 0, n-1, c); }
      else if (l >= n) { ST.ass(l-n, r-n, 0, n-1, c); }
      else { ST.ass(l, n-1, 0, n-1, c); ST.ass(0, r-n, 0, n-1, c); } }
    else if (opt == 2) {
      int l=sc.n(), r=sc.n(), c=sc.n(); l += stp-1; r += stp-1;
      if (r < n) { ST.add(l, r, 0, n-1, c); }
      else if (l >= n) { ST.add(l-n, r-n, 0, n-1, c); }
      else { ST.add(l, n-1, 0, n-1, c); ST.add(0, r-n, 0, n-1, c); } }
    else if (opt == 3) { (stp += sc.n()) %= n; }
    else {
      int l=sc.n(), r=sc.n(); l += stp-1; r += stp-1;
      if (r < n) { ST.add(l, r, 0, n-1, 1-l); ST.str(l, r, 0, n-1, 1); }
      else if (l >= n) { ST.add(l-n, r-n, 0, n-1, n-l+1); ST.str(l-n, r-n, 0, n-1, 1); }
      else { ST.add(l, n-1, 0, n-1, 1-l);   ST.str(l, n-1, 0, n-1, 1); 
             ST.add(0, r-n, 0, n-1, n-l+1); ST.str(0, r-n, 0, n-1, 1); } }
    //rep (i,n) putchar(ST.query((i+stp)%n,0,n-1) + 'A'); putchar('\n');
  }
  rep (i,n) putchar(ST.query((i+stp)%n,0,n-1) + 'A'); putchar('\n');
}
