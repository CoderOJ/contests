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

constexpr int M = 39989;
constexpr int W = 1000000000;

struct Line {
  double k=0, b=0;
  Line() =default;
  explicit Line(double k, double b) : k(k), b(b) {}
  explicit Line(int x0, int y0, int x1, int y1) {
    if (x0 == x1) { k=0; b = std::max(y0,y1); } 
    else { k = static_cast<double>(y1 - y0) / (x1 - x0); b = y0 - k * x0; } }
  inline double eval(double x) const { return x * k + b; }
  friend std::ostream& operator<< (std::ostream& out, const Line& l) {
    out << "y = " << l.k << "x + " << l.b; return out; }
};

struct Id { 
  double ans=0; int id=0;
  Id() =default;
  explicit Id(double ans, int id) : ans(ans), id(id) {}
  bool operator< (const Id& rhs) const {
    return ans!=rhs.ans ? ans<rhs.ans : id>rhs.id; }
};

struct LCTree {
  struct Node : public Line {
    int id=0; 
    Node() =default;
    explicit Node(const Line line, int id) : Line(line), id(id) {}
  } p[M * 4];
  static constexpr int root = 1;

  void modify(Node pos, int ml,int mr, int l=1,int r=M+1,int u=root) {
    int mid = (l + r + 1) / 2;
    if (ml <= l && r <= mr) {
      auto& ori = p[u];
      double pos_m = pos.eval(mid - 1);
      double ori_m = ori.eval(mid - 1);
      if (pos_m > ori_m) { std::swap(pos, ori); }
      double pos_l = pos.eval(l), pos_r = pos.eval(r - 1);
      double ori_l = ori.eval(l), ori_r = ori.eval(r - 1);
      if (!( (pos_l>ori_l) ^ (pos_r>ori_r) )) { return; } } 
    if (ml < mid) { modify(pos, ml,mr, l,mid, u+u); }
    if (mr > mid) { modify(pos, ml,mr, mid,r, u+u+1); } }

  Id query(int pos, int l=1,int r=M+1,int u=root) {
    int mid = (l + r + 1) / 2;
    auto res = Id(p[u].eval(pos), p[u].id);
    if (r - l == 1) { return res; }
    return std::max(res, (pos<mid ? query(pos,l,mid,u+u) : query(pos,mid,r,u+u+1))); }
} T;

int q;

void preInit() { } void init() {
  q = sc.n(); 
} void solve() {
  int last_ans = 0;
  int insert_id = 1;
  for ([[maybe_unused]] int _case: range(1,q+1)) {
    int opt = sc.n();
    if (opt == 0) {
      int p = (sc.n() + last_ans - 1 + M) % M + 1;
      printf("%d\n", last_ans = T.query(p).id); }
    else {
      int x0 = (sc.n() + last_ans - 1 + M) % M + 1;
      int y0 = (sc.n() + last_ans - 1 + W) % W + 1;
      int x1 = (sc.n() + last_ans - 1 + M) % M + 1;
      int y1 = (sc.n() + last_ans - 1 + W) % W + 1;
      if (x0 > x1) { std::swap(x0,x1); std::swap(y0,y1); }
      T.modify(LCTree::Node(Line(x0,y0,x1,y1), insert_id++), x0,x1+1); } }
}
