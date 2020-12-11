#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
#include <bits/stdc++.h>
#include "/home/jack/code/creats/body.h"

/** My code begins here **/

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

  std::size_t match(char* s) {
    std::size_t ans = 0, best = 0, cur = 0;
    int pos = root;
    while (*s) {
      std::size_t c = *s - 'a';
      while (pos != -1 && p[pos].next[c] == -1) { 
        pos = p[pos].link; 
        if (pos != -1) { cur = p[pos].len; } }
      if (pos == -1) { pos = root; cur = 0; }
      else { cur++; pos = p[pos].next[c]; }
      checkMax(best, cur);
      ans += best;
      s++; }
    return ans; 
  }
} sam_a;

char a[N], b[N];

void preInit() { } void init() {
  scanf("%s%s", a, b);
} void solve() {
  std::size_t n = std::strlen(a);
  for (std::size_t i=0; i<n; ++i) sam_a.insert(a[i] - 'a');
  std::size_t ans = 0;
  char* t = b;
  while (*t) {
    ans += sam_a.match(t);
    t++; }
  printf("%lu\n", ans);
}
