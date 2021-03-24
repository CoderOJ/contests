#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/util.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 2000005;
constexpr int C = 4;

struct GSAM {
  struct Node {
    int next[C]={-1,-1,-1,-1}, link=-1, len=0, val=0;
  } p[N * 2];
  static constexpr int root = 0;
  int last = root, cnt = last + 1;
  
  void reset() { last = root; }

  void insert(std::size_t c, int val) {
    { if (int q = p[last].next[c]; q != -1) {
        if (p[q].len == p[last].len + 1) { last = q; 
          checkMax(p[q].val, val); }
        else {
          int clone = cnt++;
          p[clone] = p[q];
          p[clone].len = p[last].len + 1;
          checkMax(p[clone].val, val); 
          p[q].link = clone;
          while (last != -1 && p[last].next[c] == q) {
            p[last].next[c] = clone; last = p[last].link; }
          last = clone; } 
        return; } }
    int cur = cnt++;
    p[cur].len = p[last].len + 1;
    p[cur].val = val;
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
        checkMax(p[clone].val, val);
        p[q].link = p[cur].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone; pos = p[pos].link; } } }
    last = cur; }

  void check() {
    int pos = p[last].link;
    while (pos != -1) {
      checkMax(p[pos].val, p[last].val);
      pos = p[pos].link; } }

  long long query(int k) {
    long long ans = 0;
    for (int i=1;i<cnt;i++) {
      if (p[p[i].link].len < k && k <= p[i].len) {
        ans += p[i].val; } }
    return ans; }

  void log() {
    for (int i=0;i<cnt;++i) {
      see(i, p[i].len, p[i].val, p[i].link); }
    for (int i=0;i<cnt;++i) {
      for (int j=0;j<C;++j) {
        if (p[i].next[j] != -1) {
          see(i,p[i].next[j], char('a'+j)); } } } }
} sam;

int n;
char s[N];

void preInit() { } void init() {
  n = sc.n();
} void solve() {
  rep (i,n) {
    int opt = sc.n();
    if (opt == 1) {
      int val = sc.n(); sc.next(s);
      char *s_p = s;
      while (*s_p) { sam.insert(*s_p++ - 'a', val); sam.check(); }
      sam.reset(); }
    else {
      int k = sc.n();
      printf("%lld\n", sam.query(k)); } }
  // sam.log();
}
