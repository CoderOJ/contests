
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
// #define int long long

/** My code begins here **/

/*
 * Segment Tree Node that supports:
 *  + interval assignment
 *  + interval accumulate
 */

struct NodeAssign {
  using value_type = int;
  int sum = 0, len = 1;

  NodeAssign() =default;
  NodeAssign(NodeAssign l, NodeAssign r) : sum(l.sum+r.sum), len(l.len+r.len) {}
  void modify(value_type val) { sum = len * val; }
};

template <class NodeType>
struct STree {
  struct Node : public NodeType {

    using value_type = typename NodeType::value_type;
    using NodeType::NodeType;
    value_type tag = value_type(); 
    bool is_modified = false;

    void modify(value_type val) {
      tag = val; is_modified = true;
      NodeType::modify(val); }
    void push_down(Node& l, Node& r) {
      if (is_modified) {
        l.modify(tag); r.modify(tag); }
      is_modified = false; }
  };

  static constexpr int root = 1;
  const int g_l, g_r;
  Node *const p;
  STree(int g_r) : g_l(0), g_r(g_r), p(new Node[(g_r - g_l) * 4]) {}
  STree(int g_l, int g_r) : g_l(g_l), g_r(g_r), p(new Node[(g_r - g_l) * 4]) {}

  void __modify(int ml, int mr, typename Node::value_type val, int l, int r, int u) {
    if (ml <= l && r <= mr) { p[u].modify(val); return; }
    p[u].push_down(p[u+u], p[u+u+1]);
    int mid = l + (r - l + 1) / 2;
    if (ml < mid) { __modify(ml,mr,val, l,mid,u+u); }
    if (mr > mid) { __modify(ml,mr,val, mid,r,u+u+1); }
    p[u] = Node(p[u+u], p[u+u+1]); }
  void modify(int ml, int mr, typename Node::value_type val) {
    if (ml >= mr) { return; }
    __modify(ml,mr,val, g_l,g_r,root); }

  NodeType __query(int ml, int mr, int l, int r, int u) {
    if (ml <= l && r <= mr) { return p[u]; }
    p[u].push_down(p[u+u], p[u+u+1]);
    int mid = l + (r - l + 1) / 2;
    if (mr <= mid) { return __query(ml,mr, l,mid, u+u); }
    if (ml >= mid) { return __query(ml,mr, mid,r, u+u+1); }
    return NodeType(__query(ml,mr, l,mid, u+u), __query(ml,mr, mid,r, u+u+1)); }
  NodeType query(int ml, int mr) {
    if (ml >= mr) { return NodeType(); }
    return __query(ml,mr, g_l,g_r,root); }

  ~STree() { delete[] p; }
};

struct Operation {
  enum Type { enc=1, dec=0 } type;
  int l, r;
};

constexpr int N = 100005;
Temps::Vector<Operation> opts;
char s[N], t[N];
int n, m;

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); sc.next(s);
  for ([[maybe_unused]] int i: range(m)) {
    int l=sc.n()-1, r=sc.n(), type=sc.n();
      opts.push_back({Operation::Type(type), l, r}); }
} void solve() {
  STree<NodeAssign> T(n);
  std::fill(t, t+n, 'a'); 
  for (char thr: range('a', 'z')) {
    for (int i: range(n)) {
      T.modify(i,i+1, s[i] > thr); }
    for (const auto [type,l,r]: opts) {
      int cnt_one = T.query(l,r).sum;
      int cnt_zero = r-l - cnt_one;
      if (type == Operation::enc) {
        T.modify(l, l+cnt_zero, 0);
        T.modify(l+cnt_zero, r, 1); }
      else {
        T.modify(l, l+cnt_one, 1); 
        T.modify(l+cnt_one, r, 0); } }
    for (int i: range(n)) {
      t[i] += T.query(i,i+1).sum; } }
  puts(t);
}
