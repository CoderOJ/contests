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

constexpr int N = 100005;

struct STree_impl {
  struct Node {
    int min=0, max=0, add=0;
    void pushAdd(int del) {
      min += del; max += del; add += del; }
    void pushDown(Node& l, Node& r) {
      l.pushAdd(add); r.pushAdd(add); add=0; }
    void pushUp(const Node& l, const Node& r) {
      min = std::min(l.min, r.min); max = std::max(l.max, r.max); }
  };

  Node p[N*4];
  static constexpr int root = 1;
  void modify(int sl, int sr, int l, int r, int del, int u=root) {
    if (sl <= l && r <= sr) { p[u].pushAdd(del); return; }
    p[u].pushDown(p[u+u], p[u+u+1]); 
    int mid = (l+r) / 2;
    if (sl <= mid) { modify(sl,sr, l,mid, del,u+u); }
    if (sr > mid) { modify(sl,sr, mid+1,r, del,u+u+1); }
    p[u].pushUp(p[u+u], p[u+u+1]); }
  int getpos(int sl, int sr, int l, int r, std::function<bool(Node&)> valid, int u=root) {
    if (l == r) { return l; }
    p[u].pushDown(p[u+u], p[u+u+1]); 
    int mid = (l+r) / 2;
    if (sl <= mid && valid(p[u+u])) { return getpos(sl,sr, l,mid, valid,u+u); }
    return getpos(sl,sr, mid+1,r, valid,u+u+1); }
};

struct Path : protected STree_impl {
};

int n, l, p;
struct MType { enum Type { inc, dec } type; int time; } mt[N];
struct DType { int delta, id; };

void preInit() { } void init() {
  n = sc.n(); l = sc.n(); p = sc.n();
  rep (i,n) {
    char op=sc.nextChar(); int time=sc.n();
    mt[i] = { (op=='+') ? MType::inc : MType::dec, time }; }
} void solve() {
}

