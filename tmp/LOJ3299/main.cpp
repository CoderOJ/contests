#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <vector>
#include <algorithm>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 2000005;

struct Operation {
  int type, t, x, y;
} ops[N];
int n;

struct STree {
  static constexpr int root = 1;
  int l, r;
  struct Node {
    int sum = 0;
    Node() =default;
    Node(const Node l, const Node r) : sum(l.sum + r.sum) {}
    void push_add(int val) { sum += val; }
  } *p;
  STree(int l, int r) : l(l), r(r), p(new Node[(r-l+1) * 4]) {}
  ~STree() { delete[] p; } 
  
  void _modify(int p, int val, int l, int r, int u) {
    if (r - l == 1) { this->p[u].push_add(val); return; }
    int mid = (l + r + 1) >> 1;
    if (p < mid) { _modify(p, val, l, mid, u+u); }
    else { _modify(p, val, mid, r, u+u+1); }
    this->p[u] = Node(this->p[u+u], this->p[u+u+1]); }
  void modify(int p, int val) { _modify(p, val, l, r, root); }
  
  Node _query(int ql, int qr, int l, int r, int u) {
    if (ql <= l && r <= qr) { return p[u]; }
    int mid = (l + r + 1) >> 1;
    if (ql >= mid) { return _query(ql, qr, mid, r, u+u+1); }
    if (qr <= mid) { return _query(ql, qr, l, mid, u+u); }
    return Node(_query(ql, qr, l, mid, u+u), _query(ql, qr, mid, r, u+u+1)); }
  Node query(int l, int r) { return _query(l, r, this->l, this->r, root); }
  
  int _queryFirst(int qval, int l, int r, int u, int suf) {
    if (r - l == 1) { return l; }
    int mid = (l + r + 1) >> 1;
    if (suf + p[u+u+1].sum < qval) { return _queryFirst(qval, l, mid, u+u, suf + p[u+u+1].sum); }
    else { return _queryFirst(qval, mid, r, u+u+1, suf); } }
  int queryFirst(int qval) { return _queryFirst(qval, l, r, root, 0); }
} ta(-1, N), tb(-1, N);

int query(int l, int r, int ta_u, int tb_u, int ta_pre, int tb_suf) {
  if (r - l == 1) { return l; } 
  int mid = (l + r + 1) >> 1;
  int ta_cur = ta_pre + ta.p[ta_u * 2].sum;
  int tb_cur = tb_suf + tb.p[tb_u * 2 + 1].sum;
  if (ta_cur <= tb_cur) { return query(mid, r, ta_u*2+1, tb_u*2+1, ta_cur, tb_suf); }
  else { return query(l, mid, ta_u*2, tb_u*2, ta_pre, tb_cur); }
}

std::vector<int> dis;
void preInit() { } void init() {
  n = sc.n();
  for (int i: range(n)) { 
    ops[i].type = sc.n();
    if (ops[i].type == 1) { 
      ops[i].t = sc.n(); ops[i].x = sc.n(); ops[i].y = sc.n(); 
      if (ops[i].t == 0) { ops[i].x--; }
      dis.push_back(ops[i].x); }
    else { ops[i].t = sc.n() - 1; } }
  std::sort(dis.begin(), dis.end()); dis.erase(std::unique(dis.begin(), dis.end()), dis.end());
  for (int i: range(n)) { ops[i].x = std::distance(dis.begin(), std::lower_bound(dis.begin(), dis.end(), ops[i].x)); }
} void solve() {
  for (int i: range(n)) {
    if (ops[i].type == 1) { (ops[i].t ? tb : ta).modify(ops[i].x, ops[i].y); }
    else { const Operation& pre = ops[ops[i].t]; (pre.t ? tb : ta).modify(pre.x, -pre.y); }
    int pos = query(-1, N, STree::root, STree::root, 0, 0);
    int ans = ta.query(-1, pos).sum, rans = tb.query(pos+1, N).sum;
    if (rans >= ans) { ans = rans; pos = tb.queryFirst(ans); }
    if (ans == 0) { puts("Peace"); }
    else { printf("%d %d\n", dis[pos], ans * 2); }
  } 
}