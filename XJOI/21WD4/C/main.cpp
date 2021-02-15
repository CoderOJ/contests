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

constexpr int N = 250005;

struct LCT {
  struct Node {
    Node *f=nullptr, *s[2] = {nullptr, nullptr};
    int rev=0;
    inline bool isRoot() const noexcept {
      return f == nullptr || (f->s[0] != this && f->s[1] != this); }
    inline bool getSon() const noexcept {
      return f->s[1] == this; }
    inline void pushRev() noexcept { std::swap(s[0], s[1]); rev ^= 1; }
    inline void pushDown() noexcept {
      if (rev) {
        if (s[0] != nullptr) { s[0]->pushRev(); }
        if (s[1] != nullptr) { s[1]->pushRev(); } 
        rev = 0; } }
    void push() noexcept {
      if (!isRoot()) { f->push(); }
      pushDown(); }
    void rotate() noexcept {
      Node *const uu=this, *const ff=f, *const aa=ff->f; int ss=getSon();
      if (!ff->isRoot()) { aa->s[ff->getSon()] = uu; }
      ff->f = uu; ff->s[ss] = uu->s[!ss];
      uu->f = aa; uu->s[!ss] = ff;
      if (ff->s[ss] != nullptr) { ff->s[ss]->f = ff; } }
    void _splay() noexcept {
      if (isRoot()) { return; }
      if (f->isRoot()) { rotate(); return; }
      (getSon() == f->getSon() ? f : this) -> rotate(); rotate();
      _splay(); }
    inline void splay() noexcept {
      push(); _splay(); }
    void access() noexcept {
      Node *uu = this, *ss = nullptr;
      while (uu != nullptr) {
        uu->splay(); uu->s[1] = ss; 
        ss = uu; uu = uu->f; } }
    inline void makeroot() noexcept {
      access(); splay(); pushRev(); }
    Node* findroot() noexcept {
      access(); splay();
      Node *u = this; pushDown();
      while (u->s[0] != nullptr) { 
        u = u->s[0]; u->pushDown(); }
      u->splay(); return u; }
  } p[N];
  
  void link(int u, int v) {
    slog("link (%d, %d)", u, v);
    p[u].makeroot(); p[u].splay(); p[u].f = &p[v]; }
  void split(int u, int v) {
    p[u].makeroot(); p[v].access(); p[v].splay(); }
  void cut(int u, int v) {
    slog("cut (%d, %d)", u, v);
    split(u, v); p[v].s[0] = p[u].f = nullptr; }
} T;

struct STree {
  struct Node {
    int min, len=1, add=0;
    inline void pushAdd(int val) noexcept {
      min += val; add += val; }
    inline void pushDown(Node& l, Node& r) noexcept {
      l.pushAdd(add); r.pushAdd(add); add=0; }
    inline void pushUp(const Node& l, const Node& r) noexcept {
      if (l.min < r.min) { min=l.min; len=l.len; }
      else if (l.min > r.min) { min=r.min; len=r.len; }
      else { min=l.min; len=l.len + r.len; } }
  } p[N * 4];

  static constexpr int root = 1;
  void init(int l, int r, int u = root) {
    if (l == r) { p[u].min = l; return; }
    int mid = (l + r) / 2;
    init(l, mid, u+u); init(mid+1, r, u+u+1);
    p[u].pushUp(p[u+u], p[u+u+1]); }
  void modify(int sl, int sr, int l, int r, int val, int u=root) {
    if (sl <= l && r <= sr) { p[u].pushAdd(val); return; }
    p[u].pushDown(p[u+u], p[u+u+1]);
    int mid = (l + r) / 2;
    if (sl <= mid) { modify(sl, sr, l, mid, val, u+u); }
    if (sr > mid) { modify(sl, sr, mid+1, r, val, u+u+1); }
    p[u].pushUp(p[u+u], p[u+u+1]); }
  Node query(int sl, int sr, int l, int r, int u = root) {
    if (sl <= l && r <= sr) { return p[u]; }
    p[u].pushDown(p[u+u], p[u+u+1]);
    int mid = (l + r) / 2;
    if (sl > mid) { return query(sl,sr, mid+1,r, u+u+1); }
    if (sr <= mid) { return query(sl,sr, l,mid, u+u); }
    Node res; res.pushUp(query(sl,sr, l,mid, u+u), query(sl,sr, mid+1,r, u+u+1));
    return res; }
} St;

int n, m;
int degree[N];
std::vector<int> e[N], d[N]; std::size_t eid[N];
std::vector<std::pair<int,int>> event[N];

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,m) { int u=sc.n(), v=sc.n();
    if (u > v) { std::swap(u,v); }
    e[v].push_back(u);
    event[1].push_back(std::make_pair(v, -1));
    event[u + 1].push_back(std::make_pair(v, 1)); }
  St.init(1, n);
} void solve() {
  long long ans = 0;

  int r = 2;
  for (int l=1; l<=n; ++l) {
    while (r <= n) {
      bool isBreak = false;
      for (std::size_t& i=eid[r]; i<e[r].size(); ++i) {
        const int u = e[r][i], v = r;
        if (u < l) { continue; }
        if (degree[u] < 2 && degree[v] < 2 &&
            T.p[u].findroot() != T.p[v].findroot()) {
          ++degree[u]; ++degree[v];
          T.link(u, v); d[u].push_back(v); }
        else { isBreak = true; break; } }
      if (isBreak) { break; }
      r++; }
    see(l, r);

    St.modify(1,n,1,n, -1);
    for (const auto& [u,dv]: event[l]) {
      St.modify(u,n, 1,n, dv); }

    if (l < r) {
      auto res = St.query(l,r-1, 1,n);
      if (res.min == 0) { ans += res.len; } }

    for (int v: d[l]) { 
      degree[v]--; degree[l]--;
      T.cut(l, v); } }

  printf("%lld\n", ans);
}
