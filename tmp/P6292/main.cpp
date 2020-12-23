#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include "/home/jack/code/safe_ptr.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

#define long long long
constexpr int N = 100005;
constexpr int C = 26;
char s[N]; int n;

namespace sam {
  struct Node {
    int next[C], link=-1, len=0;
    Node() { memset(next, -1, sizeof(next)); }
  };

  static constexpr int root = 0;
  int last = root, cnt = last + 1;
  Node p[N*2];

  int insert(std::size_t c) {
    int cur = cnt++;
    p[cur].len = p[last].len + 1;
    int pos = last;
    while (pos != -1 && p[pos].next[c] == -1) {
      p[pos].next[c] = cur; pos = p[pos].link; }
    if (pos == -1) { p[cur].link = root; }
    else { 
      int q = p[pos].next[c];
      if (p[q].len == p[pos].len + 1) { p[cur].link = q; }
      else {
        int clone = cnt++; p[clone] = p[q];
        p[clone].len = p[pos].len + 1;
        p[cur].link = p[q].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone; pos = p[pos].link; } } }
    last = cur; return cur; }
}

struct STree {
  struct Node {
    long wei, val=0, add=0;
    void pushAdd(long del) { add += del; val += wei * del; }
    void pushUp(Node& a, Node& b) { wei = a.wei + b.wei; val = a.val + b.val; }
    void pushDown(Node& a, Node& b) { a.pushAdd(add); b.pushAdd(add); add=0; }
  } p[N*4];

  static constexpr int root = 1;
  void init(int l, int r, int u=root) {
    if (l == r) { p[u].wei=1; return; }
    int mid = (l+r) / 2; init(l,mid,u+u); init(mid+1,r,u+u+1); 
    p[u].pushUp(p[u+u], p[u+u+1]); }
  void modify(int sl, int sr, int l, int r, long val, int u=root) {
    if (sl <= l && r <= sr) { p[u].pushAdd(val); return; }
    p[u].pushDown(p[u+u], p[u+u+1]);
    int mid = (l+r) / 2;
    if (sl <= mid) { modify(sl,sr,l,mid,val, u+u); }
    if (sr > mid) { modify(sl,sr,mid+1,r,val, u+u+1); }
    p[u].pushUp(p[u+u], p[u+u+1]); }
  long query(int sl, int sr, int l, int r, int u=root) {
    if (sl > sr) { return 0; }
    if (sl <= l && r <= sr) { return p[u].val; }
    p[u].pushDown(p[u+u], p[u+u+1]);
    int mid = (l+r) / 2; long res = 0;
    if (sl <= mid) { res += query(sl,sr,l,mid, u+u); }
    if (sr > mid) { res += query(sl,sr,mid+1,r, u+u+1); }
    return res; }
} st;

namespace LCT {
  struct Node {
    safe_ptr<Node> s[2], f;
    int len, minLen, samLen, las=0, lasTag=0;
    bool isRoot() { return f==nullptr || (f->s[0] != this && f->s[1] != this); }
    bool getSon() { return f->s[1] == this; }
    void pushUp() { minLen = std::min(len, std::min(s[0]->minLen, s[1]->minLen)); }
    void pushLen(int _len) { len = _len; pushUp(); }
    void pushLas(int _las) { las = _las; lasTag = _las; }
    void pushDown() {
      if (lasTag != 0) { s[0]->pushLas(lasTag); s[1]->pushLas(lasTag); }
      lasTag = 0; }
    void push() { if (!isRoot()) { f->push(); } pushDown(); }
    void rotate() {
      safe_ptr<Node> uu(this), ff(f), aa(ff->f); bool ss=getSon();
      if (!ff->isRoot()) aa->s[ ff->getSon() ] = uu;
      ff->s[ss]= uu->s[!ss]; ff->f=uu;
      uu->s[!ss] = ff; uu->f=aa;
      ff->s[ss]->f = ff;
      ff->pushUp(); uu->pushUp(); }
    void _splay() { 
      if (isRoot()) { return; }
      if (f->isRoot()) { rotate(); return; }
      (getSon() == f->getSon() ? f : this) -> rotate(); rotate();
      _splay(); }
    void splay() { push(); _splay(); }
    void access(int c) {
      safe_ptr<Node> uu(this), ss;
      while (uu != nullptr) {
        uu->splay(); uu->s[0] = ss; uu->pushUp();
        if (uu->las != 0) {
          st.modify(uu->las - uu->samLen + 1, uu->las - uu->minLen + 1, 1, n, -1); } 
        ss = uu; uu = uu->f; }
      splay(); pushLas(c);
      st.modify(c - samLen + 1, c, 1, n, 1); 
    }
  };
  Node p[N*2];
  void init() {
    safe_ptr<Node>::fall_back.minLen = std::numeric_limits<decltype(Node::len)>::max();
    p[0].pushLen(1);
    p[0].samLen = 0;
    repa (i,sam::cnt-1) {
      p[i].f = &p[ sam::p[i].link ];
      p[i].pushLen( sam::p[ sam::p[i].link ].len + 1 );
      p[i].samLen = sam::p[i].len; } }
};

struct Query { int l,r,id; } qs[2*N];
long ans[2*N]; int sam_pos[N];

void preInit(){} void init() {
  scanf("%s", s+1); n = std::strlen(s+1);
  repa (i,n) sam_pos[i] = sam::insert(s[i] - 'a'); 
  st.init(1,n); LCT::init();
} void solve() {
  int m; scanf("%d", &m); rep (i,m) { int l,r; scanf("%d%d",&l,&r); qs[i] = {l,r,i}; }
  std::sort(qs, qs+m, [](Query a, Query b) -> bool { return a.r < b.r; });
  int pos = 0;
  repa (i,n) {
    LCT::p[ sam_pos[i] ].access(i);
    while (pos < m && qs[pos].r == i) {
      ans[ qs[pos].id ] = st.query(qs[pos].l, n, 1, n); pos++; } }
  rep (i,m) printf("%lld\n", ans[i]); 
}
