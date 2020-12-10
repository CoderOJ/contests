#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
#include "/home/jack/code/creats/body.h"

/** My code begins here **/

const int N = 100005;
const int C = 26;

struct SAM {
  struct Node {
    std::size_t len = 0, size = 1, ref = 0;
    int link = -1, next[C];
    Node() { memset(next, -1, sizeof(next)); }
  };

  Node p[N*2];
  static constexpr int root = 0;
  int last = root;
  int cnt = root + 1;

  void clear() {
    while (cnt) { p[--cnt] = Node(); }
    cnt = 1; last = 0; }
  void insert(std::size_t c) {
    int cur = cnt++;
    p[cur].len = p[last].len + 1;
    int pos = last;
    while (pos != -1) {
      if (p[pos].next[c] != -1) { break; }
      p[pos].next[c] = cur;
      pos = p[pos].link; }
    if (pos == -1) { p[cur].link = 0; }
    else {
      int q = p[pos].next[c];
      if (p[q].len == p[pos].len + 1) { p[cur].link = q; }
      else {
        int clone = cnt++;
        p[clone] = p[q];
        p[clone].len = p[pos].len + 1;
        p[clone].size = 0;
        p[q].link = p[cur].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone;
          pos = p[pos].link; } } }
    last = cur; }
  void buildSize() {
    for (int i=1; i<cnt; ++i) { p[ p[i].link ].ref ++; } 
    std::queue<int> que; for (int i=0; i<cnt; ++i) if (p[i].ref == 0) { que.push(i); }
    while (!que.empty()) {
      int u = que.front(); que.pop(); 
      int fa = p[u].link;
      if (fa != -1) {
        p[fa].size += p[u].size; p[fa].ref --;
        if (p[fa].ref == 0) { que.push(fa); } } } }
  unsigned long long solve() {
    buildSize();
    unsigned long long res = 0;
    for (int i=1; i<cnt; ++i) {
      res += static_cast<unsigned long long>(p[i].len - p[ p[i].link ].len) * p[i].size * p[i].size; }
    return res; }

} sam;

int n;
char s[N];

void preInit() { } void init() {
  sam.clear();
} void solve() {
  scanf("%s", s);
  n = std::strlen(s);
  rep (i,n) { sam.insert(s[i] - 'a'); }
  printf("%llu\n", sam.solve());
}
