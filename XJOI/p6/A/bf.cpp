#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
#include "/home/jack/code/creats/body.h"

/** My code begins here **/

#define long long long
constexpr int N = 100005;
constexpr int C = 26;

struct SAM {
  struct Node {
    int next[C], link=-1, len=0;
    Node() { memset(next, -1, sizeof(next)); }
  };

  static constexpr int root = 0;
  int last = root, cnt = last + 1;
  long ans = 0;
  Node p[N*2];

  void clear() {
    rep (i,cnt) { p[i] = Node(); }
    last=ans=root; cnt = root+1; }
  inline int delta() { return p[last].len - p[ p[last].link ].len; }
  void insert(std::size_t c) {
    int cur = cnt++;
    p[cur].len = p[last].len + 1;
    int pos = last;
    while (pos != -1 && p[pos].next[c] == -1) {
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
        p[cur].link = p[q].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone;
          pos = p[pos].link; } } }
    last = cur; ans += delta(); }
};

char s[N]; int n;

long count(int sr, int ed) {
  static SAM sam; sam.clear();
  long res = 0;
  repb (i,ed,0) {
    sam.insert(s[i] - 'a'); 
    if (i <= sr) { res += sam.ans-1; } }
  return res; }

void preInit() { 
} void init() {
  scanf("%s", s); n = std::strlen(s);
} void solve() {
  long total = 0;
  long conflict = 0;

  static SAM sam; sam.clear();
  rep (i,n) {
    sam.insert(s[i] - 'a');
    total += sam.delta();
    conflict += count(sam.delta()-1, i); }
  see(conflict, total);

  total = total * (total-1) / 2;
  if (total == 0) { total = 1; }
  std::function<long(long, long)> gcd = [&](long a, long b) {
    return b == 0 ? a : gcd(b, a%b); };
  long valid = total - conflict;
  long g = gcd(valid, total);
  printf("%lld/%lld\n", valid/g, total/g);
}
