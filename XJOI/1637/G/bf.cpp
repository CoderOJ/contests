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

int a[N], n, m;

struct STree {
  int val[N];
  void build(int a[], int b, int c) {
    repi (i,b,c) val[i] = a[i]; }
  void add(int l, int r, int x, int y, int del) {
    repi (i,l,r) { (val[i % n] += del) %= 26; } }
  void ass(int l, int r, int x, int y, int del) {
    repi (i,l,r) { val[i % n] = del; } }
  void str(int l, int r, int x, int y, int del) {
    repi (i,l,r) { val[i % n] += i; } }
  int query(int pos, int l, int r) {
    return val[pos] % 26; }
} ST;

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
  }
  rep (i,n) putchar(ST.query((i+stp)%n,0,n-1) + 'A');
}
