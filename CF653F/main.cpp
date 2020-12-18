#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

constexpr int N = 500005;
constexpr int C = 2;
char s[N]; int n;
int height[N];

struct QueryLower {
  int a[N], left_lower[N];
  void init(int _a[], int n) {
    memcpy(a, _a, sizeof(*a) * n);
    std::stack<int> upp;
    for (int i=0; i<n; ++i) {
      while (!upp.empty() && a[upp.top()] >= a[i]) { upp.pop(); }
      left_lower[i] = upp.empty() ? 0 : upp.top() + 1;
      upp.push(i); } }
} ql;

struct InterHit {
  int a[N], n;
  struct QueryType { int r, val, ans; };
  QueryType qs[N*2]; std::size_t qs_top = 0;
  int _cnt[N*2], *cnt=_cnt+N;
  
  void init(int _a[], int _n) {
    n = _n; memset(_cnt, 0, sizeof(_cnt));
    memcpy(a, _a, sizeof(*a) * n); }
  void regQuery(int l, int r, int val) {
    slog("REGISTER QUERY: l=%d, r=%d, val=%d\n", l,r,val);
    qs[qs_top++] = {l-1, val, -1};
    qs[qs_top++] = {r, val, 1}; }
  long long getAns() {
    std::sort(qs, qs+qs_top, [](QueryType a, QueryType b) { return a.r < b.r; });
    int pos = 0; while (pos<qs_top && qs[pos].r < 0) { qs[pos].ans = 0; pos++; }
    for (std::size_t i=0; i<n; ++i) {
      cnt[a[i]] ++;
      while (pos < qs_top && qs[pos].r <= i) {
        qs[pos].ans *= cnt[qs[pos].val]; pos++; } }
    long long res = 0;
    for (std::size_t i=0; i<qs_top; ++i) { 
      res += qs[i].ans; }
    return res; }
} hit;

struct SAM {
  struct Node {
    int next[C], link=-1, len=0, pos=0;
    Node () { memset(next, -1, sizeof(next)); }
  };

  Node p[N*2];
  static constexpr int root = 0;
  int last = root, cnt = root + 1;

  void insert(std::size_t c) {
    int cur = cnt++;
    p[cur].len = p[last].len + 1;
    p[cur].pos = p[cur].len;
    int pos = last;
    while (pos != -1) {
      if (p[pos].next[c] != -1) { break; }
      p[pos].next[c] = cur;
      pos = p[pos].link; }
    if (pos == -1) { p[cur].link = root; } 
    else {
      int q = p[pos].next[c];
      if (p[q].len == p[pos].len + 1) { p[cur].link = q; }
      else {
        int clone = cnt++;
        p[clone] = p[q];
        p[clone].len = p[pos].len + 1;
        p[cur].link = p[q].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone;
          pos = p[pos].link; } } }
    last = cur; }

  long long solve() {
    for (int i=1; i<cnt; ++i) {
      int len = p[i].len, pos = p[i].pos;
      int l = pos - len, r = pos - p[ p[i].link ].len;
      checkMax(l, ql.left_lower[pos]);
      if (l >= r) { continue; }
      hit.regQuery(l, r-1, height[pos]); }
    return hit.getAns(); }
} sam;

void preInit() { } void init() {
  scanf("%d%s", &n, s); 
} void solve() {
  rep (i,n) height[i+1] = height[i] + (s[i] == '(' ? 1 : -1);
  logArray(height,n+1);
  ql.init(height, n+1); hit.init(height, n+1);
  logArray(ql.left_lower,n+1);
  rep (i,n) sam.insert(s[i] == ')');
  printf("%lld\n", sam.solve());
}
