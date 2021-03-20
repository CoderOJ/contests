#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
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
#define int long long

/** My code begins here **/

int h, q;

template <class T1, class T2> 
std::pair<T1,T2> operator+ (const std::pair<T1,T2>& a, const std::pair<T1,T2>& b) {
  return {a.first + b.first, std::max(a.second, b.second)}; }

struct STree {
  struct Node {
    Node *l=nullptr, *r=nullptr;
    int32_t add=0;
    inline void push_add(int32_t del) { 
      add += del; }
    void push_down();
  };
 
  static Node pool[100000 * 50 * 4];
  static Node* allocate_Node() {
    static int cnt = 1;
    return &pool[cnt++]; }

  int l, r;
  Node *root;
 
  STree(int l, int r) : l(l), r(r), root(pool) {}
 
  void _modify(int sl, int sr, int l, int r, int32_t del, Node *&u) {
    if (sl <= l && r <= sr) { u->push_add(del); return; }
    u->push_down();
    int mid = (l + r) / 2;
    if (sl < mid) { _modify(sl,sr, l,mid, del, u->l); }
    if (sr > mid) { _modify(sl,sr, mid,r, del, u->r); } }
  void modify(int l, int r, int32_t del) { 
    checkMax(l, this->l); checkMin(r, this->r); 
    if (l >= r) { return; }
    _modify(l,r,this->l,this->r,del,root); }
  
  std::pair<int,int> _query(int l, int r, int k, Node *u) {
    if (u->l==nullptr && u->r==nullptr) { 
      return u->add == k ? std::make_pair(r-l,l) : std::make_pair(0ll,0ll); }
    u->push_down();
    int mid = (l + r) / 2;
    return _query(l, mid, k, u->l) + _query(mid, r, k, u->r); }
  std::pair<int,int> query(int k) { return _query(l,r,k,root); }
 
};

STree::Node STree::pool[100000 * 50 * 4];
void STree::Node::push_down() {
  if (l == nullptr) { l = allocate_Node(); }
  if (r == nullptr) { r = allocate_Node(); }
  if (l) { l->push_add(add); }
  if (r) { r->push_add(add); }
  add = 0; }


inline int k_ls(int u, int k) { return u << k; }
inline int k_rs(int u, int k) {
  while (k--) { u = u * 2 + 1; } return u; }

void preInit() { } void init() {
  h = sc.n(); q = sc.n();
} void solve() {
  int pl = (1ll << (h-1)), pr = (1ll << h);
  STree st(pl, pr);
  for ([[maybe_unused]] int _: range(q)) {
    int i=sc.n(), l=sc.nl(), r=sc.nl(), yn=sc.n();
    l = k_ls(l, h-i), r = k_rs(r, h-i) + 1;
    if (yn == 0) { st.modify(pl,pr,1); st.modify(l,r,-1); }
    else { st.modify(l,r,1); } }
  const auto r = st.query(q);
  if (r.first == 0) { puts("Game cheated!"); }
  else if (r.first > 1) { puts("Data not sufficient!"); }
  else { printf("%lld\n", r.second); }
}
