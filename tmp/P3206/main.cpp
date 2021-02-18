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

constexpr int N = 20004;
[[maybe_unused]] constexpr int M = 50004;
typedef std::pair<int, int> max_type;

int last_update[M], u[M], v[M], w[M];
int n, m, q;

struct LCT {
  struct Node {
    Node *f=nullptr, *s[2] = {nullptr, nullptr}; int rev = 0;
    max_type val = max_type(std::numeric_limits<int>::min(), -1), max=val;

    inline bool isRoot() const noexcept {
      return f==nullptr || (f->s[0] != this && f->s[1] != this); }
    inline bool getSon() const noexcept {
      return f->s[1] == this; }
    inline void pushUp() noexcept {
      max = val;
      if (s[0] != nullptr) { checkMax(max, s[0]->max); }
      if (s[1] != nullptr) { checkMax(max, s[1]->max); } }
    inline void pushRev() noexcept {
      rev ^= 1; std::swap(s[0], s[1]); }
    inline void pushDown() noexcept {
      if (rev) {
        if (s[0] != nullptr) { s[0]->pushRev(); }
        if (s[1] != nullptr) { s[1]->pushRev(); } }
        rev = 0; }
    void push() noexcept {
      if (!isRoot()) { f->push(); }
      pushDown(); }
    void rotate() noexcept {
      Node *const uu=this, *const ff=f, *const aa=ff->f; int ss = getSon();
      if (!ff->isRoot()) { ff->f->s[ff->getSon()] = uu; }
      ff->f = uu; ff->s[ss] = uu->s[!ss];
      uu->f = aa; uu->s[!ss] = ff;
      if (ff->s[ss] != nullptr) { ff->s[ss]->f = ff; }
      ff->pushUp(); uu->pushUp(); }
    void _splay() noexcept {
      if (isRoot()) { return; }
      if (f->isRoot()) { rotate(); return; }
      (getSon() == f->getSon() ? f : this) -> rotate(); rotate();
      _splay(); }
    Node* splay() noexcept {
      push(); _splay(); return this; }
    void access() noexcept {
      Node *uu=this, *ss=nullptr;
      while (uu != nullptr) {
        uu->splay(); uu->s[1] = ss; uu->pushUp();
        ss = uu; uu = uu->f; } }
    void makeRoot() noexcept {
      access(); splay(); pushRev(); }
    Node* findRoot() noexcept {
      access(); splay();
      Node* uu=this; uu->pushDown();
      while (uu->s[0] != nullptr) {
        uu = uu->s[0]; uu->pushDown(); }
      return uu->splay(); }
  } p[N * 2];

private:
  std::stack<int> spare;
  std::tuple<int,int,int> m_info[N * 2];
  struct Operation {
    enum OptType { Link, Cut } type;
    int u, v, w, mid;
  };
  std::stack<Operation> opts;

  inline int get_spare_id() noexcept {
    int res = spare.top(); spare.pop();
    return res; }
  inline void return_spare_id(int _id) noexcept {
    spare.push(_id); }

  void __link(Node* u, Node* v) noexcept {
    u->makeRoot(); u->f = v; }
  void __cut(Node* u, Node* v) noexcept {
    u->makeRoot(); v->access(); v->splay();
    v->s[0] = u->f = nullptr; v->pushUp(); }

public:
  void init(int n) noexcept {
    for (int i=n+1; i<n*2; ++i) {
      spare.push(i); } }
  inline int time_stamp() const noexcept { return opts.size(); }

  void link(int u, int v, int w) noexcept {
    slog("link (%d,%d) : %d",u,v,w);
    int _mid = get_spare_id(); 
    m_info[_mid] = std::make_tuple(u, v, w);
    opts.push({Operation::Link, u,v,w, _mid});
    p[_mid] = Node(); p[_mid].max = p[_mid].val = std::make_pair(w, _mid);
    __link(&p[u], &p[_mid]); __link(&p[_mid], &p[v]); }
  void cut(int id) noexcept {
    const auto& [u,v,w] = m_info[id];
    slog("cut (%d,%d) : %d",u,v,id);
    opts.push({Operation::Cut, u,v,w, id});
    __cut(&p[u], &p[id]); __cut(&p[v], &p[id]); 
    return_spare_id(id); }
  auto get_max(int u, int v) noexcept {
    p[u].makeRoot(); p[v].access(); p[v].splay();
    return p[v].max; }
  void rollback(int stamp) {
    while (time_stamp() > stamp) {
      auto pos = opts.top(); opts.pop();
      if (pos.type == Operation::Link) { cut(pos.mid); }
      else { link(pos.u, pos.v, pos.w); }
      opts.pop(); } }

};

struct STree {
  LCT T;
  struct Node {
    std::vector<std::tuple<int, int, int>> events;
  } p[M * 4];
  long long ans[M], cur = 0;

  static constexpr int root = 1;
  void init(int n) { T.init(n); }
  void apply(int sl,int sr, int l,int r, const std::tuple<int,int,int>& event, int u=root) {
    if (sl <= l && r <= sr) { 
      slog("apply(%d) (%d,%d) : (%d,%d,%d)", u, l,r, std::get<0>(event), std::get<1>(event), std::get<2>(event));
      p[u].events.push_back(event); return; }
    int mid = (l + r) / 2;
    if (sl <= mid) { apply(sl,sr, l,mid, event, u+u); }
    if (sr > mid) { apply(sl,sr, mid+1,r, event, u+u+1); } }
  void main(int l, int r, int u = root) {
    slog("######### main(%d) : (%d,%d)  cur=%lld", u,l,r,cur);
    int origin_stamp = T.time_stamp(); long long origin_cur = cur;
    for (const auto& [u,v,w]: p[u].events) {
      slog("attempt (%d,%d,%d)", u,v,w);
      if (T.p[u].findRoot() != T.p[v].findRoot()) { 
        cur += w; T.link(u, v, w); }
      else { auto max = T.get_max(u, v); 
        if (max.first > w) {
          cur += w - max.first; T.cut(max.second);
          T.link(u, v, w); } } }
    if (l == r) { ans[l] = cur; }
    else { int mid = (l + r) / 2; main(l, mid, u+u); main(mid+1, r, u+u+1); }
    T.rollback(origin_stamp); cur = origin_cur; }

} St;

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); q = sc.n(); St.init(n);
  rep (i,m) { u[i]=sc.n(); v[i]=sc.n(); w[i]=sc.n(); last_update[i]=0; }
  rep (t,q) { int i=sc.n() - 1;
    St.apply(last_update[i],t, 0,q, std::make_tuple(u[i],v[i],w[i]));
    last_update[i] = t+1; w[i] = sc.n(); }
  rep (i,m) { St.apply(last_update[i],q, 0,q, std::make_tuple(u[i],v[i],w[i])); }
} void solve() {
  St.main(0,q);
  repa (i,q) { printf("%lld\n", St.ans[i]); }
}
