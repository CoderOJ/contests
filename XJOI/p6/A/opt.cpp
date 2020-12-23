#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
#include "/home/jack/code/creats/body.h"
// #define int long long

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
  long padd[N*2];
  Node p[N*2];

  void clear() {
    rep (i,cnt) { p[i] = Node(); }
    last=root; cnt = root+1; }
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
    padd[cur] = p[cur].len - p[p[cur].link].len;
    last = cur; return cur; }
}

struct STree {
  struct Node {
    long wei1, wei2, val1=0, val2=0, add=0;
    inline void pushAdd(long del) { add += del; val1 += wei1 * del; val2 += wei2 * del; }
    inline void pushUp(Node& a, Node& b) { 
      wei1 = a.wei1 + b.wei1; val1 = a.val1 + b.val1; 
      wei2 = a.wei2 + b.wei2; val2 = a.val2 + b.val2; }
    inline void pushDown(Node& a, Node& b) { a.pushAdd(add); b.pushAdd(add); add=0; }
  } p[N*4];

  static constexpr int root = 1;
  void init(long w1[], long w2[], int l, int r, int u=root) {
    p[u] = Node();
    if (l == r) { p[u].wei1=w1[l]; p[u].wei2=w2[l]; return; }
    int mid = (l+r) / 2; init(w1,w2,l,mid,u+u); init(w1,w2,mid+1,r,u+u+1); 
    p[u].pushUp(p[u+u], p[u+u+1]); }
  void modify(int sl, int sr, int l, int r, long val, int u=root) {
    // if (u==root) { slog("modify on [%d,%d] with diff %lld", sl, sr, val); }
    if (sl <= l && r <= sr) { p[u].pushAdd(val); return; }
    p[u].pushDown(p[u+u], p[u+u+1]);
    int mid = (l+r) / 2;
    if (sl <= mid) { modify(sl,sr,l,mid,val, u+u); }
    if (sr > mid) { modify(sl,sr,mid+1,r,val, u+u+1); }
    p[u].pushUp(p[u+u], p[u+u+1]); }
  long query1(int sl, int sr, int l, int r, int u=root) {
    // if (u==root) { slog("query1 on [%d,%d]", sl, sr); }
    if (sl > sr) { return 0; }
    if (sl <= l && r <= sr) { return p[u].val1; }
    p[u].pushDown(p[u+u], p[u+u+1]);
    int mid = (l+r) / 2; long res = 0;
    if (sl <= mid) { res += query1(sl,sr,l,mid, u+u); }
    if (sr > mid) { res += query1(sl,sr,mid+1,r, u+u+1); }
    return res; }
  long query2(int sl, int sr, int l, int r, int u=root) {
    // if (u==root) { slog("query2 on [%d,%d]", sl, sr); }
    if (sl > sr) { return 0; }
    if (sl <= l && r <= sr) { return p[u].val2; }
    p[u].pushDown(p[u+u], p[u+u+1]);
    int mid = (l+r) / 2; long res = 0;
    if (sl <= mid) { res += query2(sl,sr,l,mid, u+u); }
    if (sr > mid) { res += query2(sl,sr,mid+1,r, u+u+1); }
    return res; }
} st;

namespace LCT {
  struct Node {
    Node *s[2]={nullptr,nullptr}, *f=nullptr;
    int len, minLen, samLen, las=0, lasTag=0;
    inline bool isRoot() { return f==nullptr || (f->s[0] != this && f->s[1] != this); }
    inline bool getSon() { return f->s[1] == this; }
    inline void pushUp() {
      minLen = len; 
      if (s[0] != nullptr) { checkMin(minLen, s[0]->minLen); }
      if (s[1] != nullptr) { checkMin(minLen, s[1]->minLen); } }
    inline void pushLen(int _len) { len = _len; pushUp(); }
    inline void pushLas(int _las) { las = _las; lasTag = _las; }
    inline void pushDown() {
      if (lasTag != 0) {
        if (s[0] != nullptr) { s[0]->pushLas(lasTag); }
        if (s[1] != nullptr) { s[1]->pushLas(lasTag); } }
      lasTag = 0; }
    void push() { if (!isRoot()) { f->push(); } pushDown(); }
    inline void rotate() {
      Node *uu=this, *ff=f, *aa=ff->f; bool ss=getSon();
      if (!ff->isRoot()) aa->s[ ff->getSon() ] = uu;
      ff->s[ss]= uu->s[!ss]; ff->f=uu;
      uu->s[!ss] = ff; uu->f=aa;
      if (ff->s[ss] != nullptr) ff->s[ss]->f = ff;
      ff->pushUp(); uu->pushUp(); }
    void _splay() { 
      if (isRoot()) { return; }
      if (f->isRoot()) { rotate(); return; }
      (getSon() == f->getSon() ? f : this) -> rotate(); rotate();
      _splay(); }
    void splay() { push(); _splay(); }
    void access(int c) {
      Node *uu=this, *ss=nullptr;
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
    p[0] = Node();
    p[0].f = nullptr;
    p[0].pushLen(1);
    p[0].samLen = 0;
    repa (i,sam::cnt-1) {
      p[i] = Node();
      p[i].f = &p[ sam::p[i].link ];
      p[i].pushLen( sam::p[ sam::p[i].link ].len + 1 );
      p[i].samLen = sam::p[i].len; } }
};

long st1_base[N], st2_base[N];
int insert_pos[N];
void preInit() { } void init() {
  scanf("%s", s+1); n = std::strlen(s+1);
  sam::clear(); repa (i,n) insert_pos[i] = sam::insert(s[i] - 'a');
  repa (i,n) { st1_base[i]=i; st2_base[i]=1; }
  st.init(st1_base,st2_base,1,n);
  LCT::init();
} void solve() {
  unsigned long total = 0, conflict = 0;
  repa (i,n) {
    int inp = insert_pos[i], st_r = sam::padd[inp];
    total += st_r; 
    LCT::p[inp].access(i);
    unsigned long cp1 = st.query1(1,i,1,n);
    unsigned long cp2 = st.query1(st_r+1,i,1,n);
    unsigned long cp3 = st.query2(st_r+1,i,1,n) * st_r;
    conflict += cp1 - cp2 + cp3 - st_r;
  }

  if (total % 2 == 1) { total = (total-1)/2 * total; }
  else { total = (total/2) * (total-1); }
  if (total == 0) { total = 1; }
  std::function<unsigned long(unsigned long, unsigned long)> gcd = [&](unsigned long a, unsigned long b) {
    return b==0 ? a : gcd(b, a%b); };
  unsigned long valid = total - conflict;
  unsigned long g = gcd(valid, total);
  printf("%llu/%llu\n", valid/g, total/g);
}
