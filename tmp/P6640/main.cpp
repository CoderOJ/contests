#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

constexpr int N = 200005;
constexpr int C = 26;

struct SAM {
protected:
  struct Node {
    int next[C], link=-1, len=0;
    Node () { memset(next,-1,sizeof(next)); }
  };
  Node p[N*2];
  static constexpr int root = 0;
  int last = root, cnt = root + 1;

public:
  void insert(std::size_t c) {
    int cur = cnt++;
    p[cur].len = p[last].len + 1;
    int pos = last;
    while (pos != -1 && p[pos].next[c] == -1) {
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
    last = cur; }
  void parse(char* s) {
    while (*s) { insert(*s - 'a'); s++; } }

  void match(int* a, char* s) {
    int pos = 0, len = 0;
    while (*s) {
      std::size_t c = *s - 'a';
      while (pos != -1 && p[pos].next[c] == -1) {
        pos = p[pos].link; 
        if (pos != -1) { len = p[pos].len; } }
      if (pos == -1) { pos = 0; len = 0; }
      else { pos = p[pos].next[c], len++; }
      *a = len; a++; s++; } }
} sam;

struct ST {
protected:
  static constexpr int B = 19;
  int max[B][N], lg[N];

public:
  void init(int a[], int n) {
    memcpy(max[0], a, sizeof(*a) * n);
    rep (i,B-1) rep (j, n-(1<<i)) max[i+1][j] = std::max(max[i][j], max[i][j+(1<<i)]);
    lg[1] = 0; repi (i,2,n) lg[i] = lg[i>>1] + 1; }
  int query(int l, int r) {
    int len = r - l + 1, b = lg[len];
    return std::max(max[b][l], max[b][r-(1<<b)+1]); }
} st;

char s[N], t[N]; int len[N];

void preInit() { } void init() { } void solve() {
  scanf("%s%s", s, t); int n = std::strlen(s);
  sam.parse(t); sam.match(len, s); st.init(len, n);
  see(n);
  int T; scanf("%d", &T);
  while (T--) {
    int x,y; scanf("%d%d",&x,&y); x--; y--;
    int l = 0, r = y-x+1;
    while (l < r) {
      int mid = (l+r+1) / 2;
      int left_most = x + mid - 1;
      see(x,y,mid,left_most, st.query(left_most, y));
      if (st.query(left_most, y) >= mid) { l = mid; }
      else { r = mid - 1; } } 
    printf("%d\n", l); }
}
