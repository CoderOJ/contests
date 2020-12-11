#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

const int N = 500005;
const int C = 26;

struct SAM {
  struct Node {
    int next[C], link=-1;
    std::size_t len=0, size=1, ref=0;
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

  std::size_t solve() {
    std::size_t ans = 0;
    for (int i=1; i<cnt; ++i) { p[ p[i].link ].ref++; }
    std::queue<int> que; rep (i,cnt) if (p[i].ref == 0) { que.push(i); }
    while (!que.empty()) {
      int u = que.front(); que.pop();
      int fa = p[u].link;
      if (fa != -1) {
        see(u, fa, p[u].size, p[fa].size, p[fa].len);
        ans += p[fa].size * p[u].size * p[fa].len;
        p[fa].size += p[u].size;
        p[fa].ref--;
        if (p[fa].ref == 0) { que.push(fa); } } } 
    return ans; }
} sam;

char s[N];
int main() {
  scanf("%s", s);
  std::size_t n = strlen(s);
  for (int i=n-1; i>=0; i--) { sam.insert(s[i] - 'a'); }
  std::size_t ans = 0;
  for (std::size_t i=1; i<=n; ++i) { ans += i * (n-1); }
  printf("%lu\n", ans - 2 * sam.solve());
  return 0;
}
