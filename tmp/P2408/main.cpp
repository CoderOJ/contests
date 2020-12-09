#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>
#include "/home/jack/code/creats/body.h"

/** My code begins here **/

const int N = 100005;
const int C = 26;

struct SAM {
  struct Node {
    int link = -1, next[C];
    int len = 0;
    Node () { memset(next, -1, sizeof(next)); }
  };

  Node p[N*2];
  static constexpr int root = 0;
  int cnt = root + 1;
  int last = root;

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
      if (p[q].len == p[pos].len + 1) { p[cur].link = q; }
      else {
        int clone = cnt++;
        p[clone] = p[q];
        p[clone].len = p[pos].len + 1;
        p[cur].link = p[q].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone;
          pos = p[pos].link; } } }
    last = cur;
  }

  std::size_t count() {
    std::size_t ans = 0;
    for (int i=1; i<cnt; ++i) {
      ans += p[i].len - p[ p[i].link ].len; }
    return ans;
  }
} sam;

char s[N]; int n;
void preInit() { } void init() {
  scanf("%d", &n); scanf("%s", s);  
} void solve() {
  rep (i,n) sam.insert(s[i] - 'a');
  printf("%lu\n", sam.count());
}
