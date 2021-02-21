#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

constexpr int N = 3005;
constexpr int B = 12;
int dep[N], n, fa[N][B];
std::vector<int> e[N];

struct LCT {
  struct Node {
    Node *f=nullptr, *s[2];
    int assign=-1, wson=0;

    inline bool is_root() const noexcept {
      return f==nullptr || (f->s[0]!=this && f->s[1]!=this); }
    inline bool get_son() const noexcept {
      return f->s[1] == this; }
    inline void push_assign(int wson) noexcept {
      assign = wson; this->wson = wson; }
    inline void push_down() noexcept {
      if (assign != -1) {
        if (s[0] != nullptr) { s[0]->push_assign(assign); }
        if (s[1] != nullptr) { s[1]->push_assign(assign); } 
        assign = -1; } }
    void push() noexcept {
      if (!is_root()) { f->push(); } push_down(); }
    void rotate() noexcept {
      Node *const uu=this, *const ff=f, *const aa=ff->f; bool ss=get_son();
      if (!ff->is_root()) { aa->s[ff->get_son()] = uu; }
      ff->f = uu; ff->s[ss] = uu->s[!ss];
      uu->f = aa; uu->s[!ss] = ff;
      if (ff->s[ss] != nullptr) { ff->s[ss]->f = ff; } }
    void _splay() noexcept {
      if (is_root()) { return; }
      if (f->is_root()) { rotate(); return; }
      (get_son() == f->get_son() ? f : this)->rotate(); rotate(); 
      _splay(); }
    inline void splay() noexcept { push(); _splay(); }
    void access() {
      Node *uu=this, *ss=nullptr;
      while (uu != nullptr) {
        uu->splay(); uu->s[1] = ss;
        ss = uu; uu = uu->f; } }
  } p[N];
  void assign(int u, int wson) {
    p[u].access(); p[u].splay(); p[u].push_assign(wson); }
  int query(int u) {
    p[u].splay(); return p[u].wson; }
} T;

inline int ask(int u, int v) {
  std::cout << "? " << u << " " << v << std::endl;
  int res; scanf("%d", &res); return res; }
inline void setf(int u, int f) {
  fa[u][0] = f;
  for (int i=0;i<B-1;++i) fa[u][i+1] = fa[fa[u][i]][i]; }
inline int geta(int u, int d) {
  for (int i=0;i<B;++i) if (d & (1<<i)) { u = fa[u][i]; } 
  return u; }

void preInit() { } void init() {
  scanf("%d", &n); dep[1] = 0; T.assign(1,1);
  for (int i=2;i<=n;++i) dep[i] = ask(1,i);
} void solve() {
  std::vector<int> id(n-1); 
  for (int i=2;i<=n;++i) id[i-2]=i;
  std::sort(id.begin(), id.end(), [](int a, int b) { return dep[a] < dep[b]; });
  for (int i: id) {
    int u = 1;
    while (true) {
      if (e[u].size() == 0) { break; }
      int ws = T.query(u);
      int dis = ask(ws, i);
      int adep = (dep[ws] + dep[i] - dis) / 2;
      if (adep == dep[ws]) {
        u = ws; break; }
      int as = geta(ws, dep[ws]-adep-1), aa = fa[as][0];
      if (e[aa].size() == 1) { u = aa; break; }
      u = (e[aa][0] == as) ? e[aa][1] : e[aa][0]; }
    T.p[i].f = &T.p[u]; T.assign(i, i);
    setf(i,u); e[u].push_back(i); }
  printf("!");
  for (int i=2;i<=n;++i) { printf(" %d", fa[i][0]); }
  puts("");
}
