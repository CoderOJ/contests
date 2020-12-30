#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"
#include "/home/jack/code/safe_ptr.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 100005;
constexpr int C = 26;

namespace STree {
struct Node { Node *l, *r; };
int g_n;
Node pool[N*40]; std::size_t pool_top = 0;
inline Node* newNode() { return &pool[pool_top++]; }
void _modify(Node *&u, int l, int r, int p) {
  if (u == nullptr) { u = newNode(); }
  if (l == r) { return; }
  int mid = (l + r) / 2;
  if (p <= mid) { _modify(u->l, l, mid, p); }
  else { _modify(u->r, mid+1, r, p); } }
void merge(Node *&u, Node *&v) {
  if (v == nullptr) { return; }
  if (u == nullptr) { u = v; return; }
  Node *c = newNode(); *c = *u; u = c;
  merge(u->l, v->l); merge(u->r, v->r); }
bool _query(Node *&u, int sl, int sr, int l, int r) {
  if (u == nullptr || sl > sr) { return 0; }
  if (sl <= l && r <= sr) { return 1; }
  int mid = (l + r) / 2;
  if (sl > mid) { return _query(u->r, sl, sr, mid+1, r); }
  else if (sr <= mid) { return _query(u->l, sl, sr, l, mid); }
  else { return _query(u->l, sl, sr, l, mid) | _query(u->r, sl, sr, mid+1, r); } }

void init(int _g_n) { g_n = _g_n; }
void modify(Node *&u, int p) { _modify(u,0,g_n,p); }
bool query(Node *&u, int l, int r) { return _query(u,l,r,0,g_n); }
} /* STree */ 

struct SAM {
  struct Node {
    int next[C], link=-1, len=0, pos=0, ref=0; STree::Node* pset;
    Node() { memset(next, -1, sizeof(next)); } };

  static constexpr int root = 0;
  int last = root, cnt = root + 1;
  Node p[N*2];

  void insert(std::size_t c) {
    int cur = cnt++; p[cur].len = p[last].len + 1; p[cur].pos = p[cur].len;
    int pos = last;
    while (pos != -1 && p[pos].next[c] == -1) {
      p[pos].next[c] = cur; pos = p[pos].link; }
    if (pos == -1) { p[cur].link = root; }
    else {
      int q = p[pos].next[c];
      if (p[q].len == p[pos].len + 1) { p[cur].link = q; }
      else {
        int clone = cnt++;
        p[clone] = p[q]; p[clone].len = p[pos].len + 1; p[clone].pos = -1;
        p[cur].link = p[q].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone; pos = p[pos].link; } } }
    last = cur; }

  void build() {
    rep (i,cnt) if (p[i].pos != -1) { STree::modify(p[i].pset,p[i].pos); }
    repa (i,cnt-1) p[p[i].link].ref++;
    std::queue<int> que; rep (i,cnt) if (p[i].ref == 0) que.push(i); 
    while (!que.empty()) {
      int u = que.front(), fa=p[u].link; que.pop();
      if (p[u].link == -1) { continue; }
      STree::merge(p[fa].pset, p[u].pset); p[fa].ref--;
      if (p[fa].ref == 0) { que.push(fa); } } }

  typedef int State;
  static constexpr State start() { return root; }
  bool hasNext(State u, std::size_t c, int l, int r) {
    int v = p[u].next[c]; if (v == -1) { return false; }
    return STree::query(p[v].pset, l, r); }
  inline State getNext(State u, std::size_t c) { return p[u].next[c]; }
} sam;

char s[N * 2]; int n;

void preInit() { } void init() {
  scanf("%s", s); n = std::strlen(s); STree::init(n);
  rep (i,n) sam.insert(s[i] - 'a'); sam.build();
} void solve() {
  int q; scanf("%d", &q);
  while (q--) {
    int l, r; scanf("%d%d%s", &l, &r, s); 
    int n = std::strlen(s); s[n] = '`'; n++; s[n] = '\0';
    int last_pos = -1, last_char = '\0';
    SAM::State pos = SAM::start();
    rep (i,n) {
      repi (j, s[i]-'a'+1, 'z'-'a') {
        if (sam.hasNext(pos, j, l, r)) {
          last_pos = i; last_char = 'a' + j; break; } }
      if (i != n-1 && sam.hasNext(pos, s[i]-'a', l, r)) {
        pos = sam.getNext(pos, s[i]-'a'); }
      else { break; } 
      l++; }
    if (last_pos == -1) { puts("-1"); }
    else { s[last_pos] = '\0'; printf("%s%c\n", s, last_char); } }
}
