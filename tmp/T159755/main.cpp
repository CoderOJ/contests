#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
#include <bits/stdc++.h>
#include "/home/jack/code/creats/body.h"

/** My code begins here **/

#define long long long

const int N = 1000005;
const int C = 26;

struct SAM {
  struct Node {
    int next[C], link=-1, len=0;
    Node () { memset(next, -1, sizeof(next)); }
  };

  Node p[N*2];
  static constexpr int root = 0;
  int last = root, cnt = root + 1;

  void insert(std::size_t c) {
    int cur = cnt++;
    p[cur].len = p[last].len + 1;
    int pos = last;
    while (pos != -1) {
      if (p[pos].next[c] != -1) { break; }
      p[pos].next[c] = cur;
      pos = p[pos].link; }
    if (pos == -1) { p[cur].link = root; }
    else {
      int q = p[pos].next[c];
      if (p[q].len == p[pos].len + 1) { 
        p[cur].link = q; }
      else {
        int clone = cnt++;
        p[clone] = p[q];
        p[clone].len = p[pos].len + 1;
        p[q].link = p[cur].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone;
          pos = p[pos].link; } } }
    last = cur;
  }

  void match(int* output, char* s) {
    int cur = 0;
    int pos = root;
    while (*s) {
      std::size_t c = *s - 'a';
      while (pos != -1 && p[pos].next[c] == -1) { 
        pos = p[pos].link; 
        if (pos != -1) { cur = p[pos].len; } }
      if (pos == -1) { pos = root; cur = 0; }
      else { cur++; pos = p[pos].next[c]; }
      *output = cur;
      s++; output++; }
  }
} sam_a;

char a[N], b[N];
int match_b[N];

template <class T> T intervalSum(T a, T b) {
  T cnt = std::abs(a - b) + 1;
  return (a + b) * cnt / 2; }

struct Ds {
  struct Unit {
    long l, r, lv, rv;
    long calc() {
      if (lv == rv) { return lv * (r-l+1); }
      else { return intervalSum(lv, rv); } }
    void log() { see(l,r,lv,rv); }
  };
  
  Unit a[N]; int top=0, id=0;
  long ans = 0;
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
    id++;
    // rep (i,top) { see(i); a[i].log(); }
  }
} ds;

void preInit() { } void init() {
  scanf("%s%s", a, b);
} void solve() {
  std::size_t n = std::strlen(a);
  std::size_t m = std::strlen(b);
  for (std::size_t i=0; i<n; ++i) sam_a.insert(a[i] - 'a');
  sam_a.match(match_b, b);
  // logArray(match_b, m);
  long ans = 0;
  for (std::size_t i=0; i<m; ++i) {
    ds.insert(match_b[i]); ans += ds.ans; }
  printf("%lld\n", ans);
}
