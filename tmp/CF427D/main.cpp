#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 5005;
constexpr int M = 2;
constexpr int C = 26;

struct GSAM {
protected:
  struct Node {
    int next[C], link=-1, size[M], len=0, ref=0;
    Node () { memset(next, -1, sizeof(next)); memset(size, 0, sizeof(size)); }
  };

  Node p[N*M*2];
  static constexpr int root = 0;
  int last = root, cnt = root + 1, bel = 0;

public:
  void reset() { last = root; bel++; }
  void insert(std::size_t c) {
    { int ss = p[last].next[c];
      if (ss != -1 && p[ss].len == p[last].len + 1) {
        last = ss; p[ss].size[bel] = 1; return; } }
    int cur = cnt++;
    p[cur].len = p[last].len + 1;
    p[cur].size[bel] = 1;
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
        memcpy(p[clone].next, p[q].next, sizeof(p[q].next));
        p[clone].link = p[q].link;
        p[clone].len = p[pos].len + 1;
        p[q].link = p[cur].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone;
          pos = p[pos].link; } } }
    last = cur; }
  void build() {
    for (int i=1; i<cnt; ++i) { p[ p[i].link ].ref++; }
    std::queue<int> que; for (int i=0; i<cnt; ++i) if (p[i].ref == 0) { que.push(i); }
    while (!que.empty()) {
      int u = que.front(); que.pop();
      int fa = p[u].link;
      if (fa != -1) {
        for (int j=0; j<M; ++j) p[fa].size[j] += p[u].size[j];
        p[fa].ref--; if (p[fa].ref == 0) { que.push(fa); } } } }
  int find() {
    int res = std::numeric_limits<int>::max();
    for (int i=1; i<cnt; ++i) {
      if (p[i].size[0] == 1 && p[i].size[1] == 1) {
        checkMin(res, p[ p[i].link ].len + 1); } }
    return res; }
} sam;

void preInit() { } void init() { } void solve() {
  static char s[N];
  for (int i=0; i<2; ++i) { 
    scanf("%s", s); int l=std::strlen(s); 
    rep (i,l) { sam.insert(s[i] - 'a'); } 
    sam.reset(); }
  sam.build();
  int ans = sam.find();
  printf("%d\n", ans == std::numeric_limits<int>::max() ? -1 : ans);
}
