#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include <bits/stdc++.h>
#include "/home/jack/code/creats/body.h"
/** My code begins here **/

const int N = 250005;
const int C = 26;

struct SAM {
  struct Node {
    int link = -1, next[C];
    std::size_t len = 0;
    Node() { memset(next, -1, sizeof(next)); }
  };

  Node p[N*2];
  static constexpr int root = 0;
  int last = root;
  int cnt = root + 1;

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
        p[q].link = p[cur].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone;
          pos = p[pos].link; } } }
    last = cur;
  }

  std::size_t match(char* s) {
    std::size_t ans = 0, cur = 0;
    int pos = root;
    while (*s) {
      std::size_t c = *s - 'a';
      while (pos != -1 && p[pos].next[c] == -1) { 
        pos = p[pos].link; cur = p[pos].len; }
      if (pos == -1) { pos = root; cur = 0; }
      else { 
        pos = p[pos].next[c]; cur++;
        if (cur > ans) { ans = cur; } } 
      s++; }
    return ans;
  }

} sam;

char a[N], b[N];

void preInit() { } void init() {
  scanf("%s", a); scanf("%s", b);
} void solve() {
  std::size_t la = strlen(a);
  for (int i=0; i<la; ++i) sam.insert(a[i] - 'a');
  printf("%lu\n", sam.match(b));
}
