#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 100005;
constexpr int C = 26;

struct SAM {
  struct Node {
    int next[C], link=-1, len=0, ref=0;
    Node() { memset(next, -1, sizeof(next)); }
  };

  Node p[N*2]; int ptos[N];
  static constexpr int root = 0;
  int last = root, cnt = last + 1;

  void insert(std::size_t c) {
    int cur = cnt++;
    ptos[ p[cur].len = p[last].len + 1 ] = cur;
    int pos = last;
    while (pos != -1 && p[pos].next[c] == -1) {
      p[pos].next[c] = cur; pos = p[pos].link; }
    if (pos == -1) { p[cur].link = root; }
    else { int q = p[pos].next[c];
      if (p[q].len == p[pos].len + 1) { p[cur].link = q; }
      else {
        int clone = cnt++;
        p[clone] = p[q];
        p[clone].len = p[pos].len + 1;
        p[cur].link = p[q].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone; pos = p[pos].link; } } }
    last = cur; }
  void build() {
    repa (i,cnt-1) { p[p[i].link].ref++; } }
  int query(int pos) {
    pos = ptos[pos];
    if (p[pos].ref) { return -1; }
    return p[p[pos].link].len + 1; }
} sam;

char s[N]; int n, l[N], ans[N];

void preInit() { } void init() {
  scanf("%s", s); n = std::strlen(s);
  rep (i,n) sam.insert(s[i] - 'a');
  sam.build();
} void solve() {
  rep (i,n) l[i] = sam.query(i+1); 
  memset(ans, 0x3f, sizeof(ans)); 
  rep (i,n) if (l[i] != -1) {
    int s = i - l[i] + 1;
    int t = i;
    rep (j,n) {
      checkMin(ans[j], std::max(t,j) - std::min(s,j) + 1); } }
  rep (i,n) printf("%d\n", ans[i]);
}
