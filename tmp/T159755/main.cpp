#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
#include <bits/stdc++.h>
#include "/home/jack/code/creats/body.h"

/** My code begins here **/

#define long long long

const int N = 3000005;

template <class T> T intervalSum(T a, T b) {
  T cnt = std::abs(a - b) + 1;
  return (a + b) * cnt / 2; }

struct Ds {
  struct Unit {
    long l, r, lv, rv;
    long calc() {
      if (lv == rv) { return lv * (r-l+1); }
      else { return intervalSum(lv, rv); } }
  };
  
  Unit a[N]; int top=0, id=0;
  unsigned long ans = 0;
  void insert(int v) {
    if (v == 0) { id++; return; }
    int pre = id - v + 1;
    while (top) {
      Unit& b = a[top-1];
      if (b.l < pre) {
        if (b.lv > v) {
          ans -= b.calc();
          b.r = b.l + b.lv - v;
          b.rv = b.lv - (b.r - b.l);
          ans += b.calc();
          break; }
        else { ans -= b.calc(); } }
      else { ans -= b.calc(); }
      top--; }
    if (top == 0) {
      if (pre != 0) {
        a[top] = {0, pre-1, v, v}; ans += a[top].calc(); top++; }
      a[top] = {pre, id, v, 1}; ans += a[top].calc(); top++; }
    else {
      int rr = a[top-1].r;
      if (rr != pre-1) {
        a[top] = {rr+1, pre-1, v, v}; ans += a[top].calc(); top++; }
      a[top] = {pre, id, v, 1}; ans += a[top].calc(); top++; }
    id++; }
} ds;

int a[N], n;

void preInit() { } void init() {
  n = sc.n(); 
  rep (i,n) a[i] = sc.n();
} void solve() {
  unsigned long res = 0;
  repb (i,n-2,0) checkMin(a[i], a[i+1]);
  repa (i,n) { ds.insert(i-a[i]+1); res += ds.ans; }
  printf("%llu\n", res);
}
