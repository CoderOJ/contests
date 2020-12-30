#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
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

constexpr int N = 100005;
constexpr int C = 26;
constexpr int B = 18;

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
  if (u == nullptr) { return 0; }
  if (sl <= l && r <= sr) { return true; }
  int mid = (l + r) / 2;
  if (sl > mid) { return _query(u->r, sl, sr, mid+1, r); }
  else if (sr <= mid) { return _query(u->l, sl, sr, l, mid); }
  else { return _query(u->l, sl, sr, l, mid) || _query(u->r, sl, sr, mid+1, r); } }

void init(int _g_n) { g_n = _g_n; }
void modify(Node *&u, int p) { _modify(u,0,g_n,p); }
bool query(Node *&u, int l, int r) { return _query(u,l,r,0,g_n); }
} /* STree */ 

struct SAM {
  struct Node {
    int next[C], link=-1, len=0, pos=0, ref=0; STree::Node* pset; int f[B];
    Node() { memset(next, -1, sizeof(next)); } };

  static constexpr int root = 0;
  int last = root, cnt = root + 1;
  Node p[N*2]; int sid[N];

  void insert(std::size_t c) {
    int cur = cnt++; p[cur].len = p[last].len + 1; p[cur].pos = p[cur].len; sid[p[cur].len] = cur;
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
    std::vector<int> ord; std::queue<int> que; rep (i,cnt) if (p[i].ref == 0) que.push(i); 
    while (!que.empty()) {
      int u = que.front(), fa=p[u].link; que.pop(); ord.push_back(u); 
      if (fa != -1) { p[fa].ref--; if (p[fa].ref == 0) { que.push(fa); } } }
    for (int u: ord) { int fa = p[u].link; if (fa != -1) { STree::merge(p[fa].pset, p[u].pset); } }
    p[root].link = root; std::reverse(ord.begin(), ord.end());
    for (int u: ord) { p[u].f[0] = p[u].link; rep (i,B-1) p[u].f[i+1] = p[p[u].f[i]].f[i]; } }

  int findPos(int pos, int len) {
    pos = sid[pos];
    repb (i,B-1,0) if (p[p[pos].f[i]].len >= len) { pos = p[pos].f[i]; }
    return pos; }
  bool exist(int pos, int l, int r) { 
    return STree::query(p[pos].pset, l, r); }
} sam;

int n, m;

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); STree::init(n);
  rep (i,n) sam.insert(sc.nextChar() - 'a'); 
  sam.build();
} void solve() {
  while (m--) {
    int a=sc.n(), b=sc.n(), c=sc.n(), d=sc.n();
    int l = 0, r = std::min(b-a+1, d-c+1);
    while (l < r) {
      int mid = (l + r + 1) / 2;
      int pos = sam.findPos(c+mid-1, mid);
      if (sam.exist(pos, a+mid-1, b)) { l = mid; }
      else { r = mid - 1; } }
    printf("%d\n", l); }
}
