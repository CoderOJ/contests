#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

constexpr int N = 1000005;
constexpr int C = 26;

struct SAM {
protected:
  struct SNode {
    int next[C], link=-1, len=0, size=1, ref=0; 
    SNode () { memset(next, -1, sizeof(next)); }
  };

  static constexpr int root = 0;
  SNode p[N * 2]; int cnt = root + 1, last = root;

public:
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
        p[clone].size = 0;
        p[q].link = p[cur].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone;
          pos = p[pos].link; } } }
    last = cur; }

  void build() {
    for (int i=1; i<cnt; ++i) { p[ p[i].link ].ref++; }
    std::queue<int> que; rep (i,cnt) if (p[i].ref == 0) { que.push(i); }
    while (!que.empty()) {
      int u = que.front(); que.pop();
      int fa = p[u].link;
      if (fa != -1) {
        p[fa].size += p[u].size;
        p[fa].ref--; if (p[fa].ref==0) { que.push(fa); } } } }
};

struct JSAM : protected SAM {
protected:
  int pos = SAM::root, len = 0, n = 0;

public:
  using SAM::insert;
  using SAM::build;
  void reset(int _n) { pos = SAM::root; len = 0; n = _n; }
  void move(std::size_t c) {
    while (pos != -1 && p[pos].next[c] == -1) {
      pos = p[pos].link; 
      if (pos != -1) { len = p[pos].len; } }
    if (pos == -1) { pos = 0; len = 0; }
    else { pos = p[pos].next[c]; len++; } }
  void erase() {
    if (len == 0) { return; } len--;
    if (p[ p[pos].link ].len == len) { pos = p[pos].link; } }
  inline int getSize() { return len == n ? p[pos].size : 0; }
  inline int getLen() { return len; }
} sam;

namespace Kmp {
int pre[N];
int getLoop(char s[], int n) {
  pre[0] = 0;
  for (int i=1; i<n; ++i) {
    int pos = pre[i-1];
    while (pos && s[pos] != s[i]) { pos = pre[pos-1]; }
    if (s[pos] == s[i]) pos++;
    pre[i] = pos; }
  int ans = pre[n-1];
  return ans*2 >= n && n % (n-ans) == 0 ? n-ans : n;
}
} /* namespace Kmp */

char s[N];
void preInit() { } void init() { } void solve() {
  scanf("%s", s); int l = std::strlen(s); rep (i,l) sam.insert(s[i]-'a'); sam.build();
  int n; scanf("%d", &n);
  rep (i,n) {
    scanf("%s", s); l = std::strlen(s);
    sam.reset(l); rep (i,l) sam.move(s[i] - 'a');
    long long ans = 0;
    int lim = Kmp::getLoop(s, l);
    rep (i,lim) { if (sam.getLen() == l) { sam.erase(); } sam.move(s[i] - 'a'); ans += sam.getSize(); } 
    printf("%lld\n", ans); }
}
