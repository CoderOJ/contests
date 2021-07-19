#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 200005;
constexpr int C = 26;

namespace SGT {
struct Node {
  Node *l=nullptr, *r=nullptr; int sum;
  void push_up() { sum = (l ? l->sum : 0) + (r ? r->sum : 0); } };
Node pool[N * 40];
static Node *newNode() { static Node *last = pool; return last++; }
int gl, gr;
void modify(Node *&u, int l, int r, int pos) {
  if (u == nullptr) { u = newNode(); }
  if (r - l == 1) { u->sum = 1; return; }
  int mid = (l + r) / 2;
  if (pos < mid) modify(u->l, l, mid, pos);
  else modify(u->r, mid, r, pos); 
  u->push_up(); }
Node *merge(Node *u, Node *v) {
  if (u == nullptr) return v;
  if (v == nullptr) return u;
  Node *r = newNode();
  r->sum = u->sum + v->sum;
  r->l = merge(u->l, v->l); r->r = merge(u->r, v->r);
  return r; }
int query(Node *u, int l, int r, int ql, int qr) {
  if (u == nullptr) return 0;
  if (ql <= l && r <= qr) return u->sum;
  int mid = (l + r) / 2;
  return (ql<mid ? query(u->l,l,mid,ql,qr) : 0) + (qr>mid ? query(u->r,mid,r,ql,qr) : 0); } }
using SGT::gl, SGT::gr;

struct GSAM {
  struct Node {
    int next[C], link=-1, len=0, ref=0; SGT::Node *t = nullptr;
    Node() { memset(next, -1, sizeof(next)); }
  } p[N * 2];
  static constexpr int root = 0;
  int last = root, cnt = last + 1, id=0;

  void reset() { last = root; id++; }
  void insert(size_t c) {
    int q = p[last].next[c];
    if (q != -1) {
      if (p[q].len == p[last].len + 1) { last = q; } 
      else { const int clone = cnt++;
        p[clone].len = p[last].len + 1; p[clone].link = p[q].link;
        memcpy(p[clone].next, p[q].next, sizeof(p[q].next));
        p[q].link = clone;
        int pos = last;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone; pos = p[pos].link; }
        last = clone; } }
    else {
      int cur = cnt++; p[cur].len = p[last].len + 1;
      int pos = last;
      while (pos != -1 && p[pos].next[c] == -1) {
        p[pos].next[c] = cur; pos = p[pos].link; }
      if (pos == -1) { p[cur].link = root; }
      else { int q = p[pos].next[c]; 
        if (p[q].len == p[pos].len + 1) { p[cur].link = q; }
        else { const int clone = cnt++;
          p[clone].len = p[pos].len + 1; p[clone].link = p[q].link;
          memcpy(p[clone].next, p[q].next, sizeof(p[q].next));
          p[q].link = p[cur].link = clone;
          while (pos != -1 && p[pos].next[c] == q) {
            p[pos].next[c] = clone; pos = p[pos].link; } } }
      last = cur; }
    see(last);
    SGT::modify(p[last].t, gl, gr, id); }
  void build() {
    for (int i=1; i<cnt; i++) { p[p[i].link].ref++; }
    static int stack[N * 2]; int *front=stack, *back=stack;
    for (int i=0; i<cnt; i++) if (p[i].ref == 0) *back++ = i;
    while (true) {
      int u = *front++; if (u == 0) break;
      p[p[u].link].t = SGT::merge(p[p[u].link].t, p[u].t);
      if (--p[p[u].link].ref == 0) *back++ = p[u].link; } }
} gsam;

int last_pos[N];
char s[N];
int n, q;

void preInit() { } 
void init() 
{
  n = sc.n(); q = sc.n();
  gl = 0, gr = n;
  for (int i=0; i<n; i++) {
    sc.next(s); size_t len = std::strlen(s);
    for (size_t j=0; j<len; j++) { gsam.insert(static_cast<size_t>(s[j] - 'a')); }
    last_pos[i] = gsam.last; gsam.reset(); }
  gsam.build();
} 

void solve() 
{
  for (int i=0; i<q; i++) {
    int l=sc.n()-1, r=sc.n(), k=sc.n()-1;
    printf("%d\n", SGT::query(gsam.p[last_pos[k]].t, gl,gr, l,r)); }
}
