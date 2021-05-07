#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 200015;

struct STree {
  struct Node {
    int min=0, add=0;
    Node() =default;
    Node(const Node l, const Node r) : 
      min(std::min(l.min, r.min)), add(0) {}
    void modify(int delta) { min += delta; add += delta; }
    void push_down(Node &l, Node &r) {
      if (add) { l.modify(add); r.modify(add); add=0; } } };
  Node p[N * 4];

  void modify(int ml, int mr, int val, int l, int r, int u) {
    if (ml <= l && r <= mr) { p[u].modify(val); return; }
    p[u].push_down(p[u + u], p[u + u + 1]);
    int mid = (l + r) / 2;
    if (ml < mid) modify(ml, mr, val, l, mid, u + u);
    if (mr > mid) modify(ml, mr, val, mid, r, u + u + 1); 
    p[u] = Node(p[u + u], p[u + u + 1]); }

  int query(int ql, int qr, int l, int r, int u) {
    if (ql <= l && r <= qr) { return p[u].min; }
    p[u].push_down(p[u + u], p[u + u + 1]);
    int mid = (l + r) / 2;
    if (qr <= mid) return query(ql, qr, l, mid, u + u);
    if (ql >= mid) return query(ql, qr, mid, r, u + u + 1);
    return std::min(query(ql, qr, l, mid, u + u), query(ql, qr, mid, r, u + u + 1)); } 
} T;

int n, q;
struct Opt { 
  int type, id,  k; 
  Opt(int type, int id, int k=0) : type(type), id(id), k(k) {} };

std::vector<Opt> ml[N], mr[N], qs[N];
int opt2val[N], ans[N];
constexpr int sgt_root = 1;
int sgt_l, sgt_r;

void preInit() { } void init() {
  n = sc.n(); q = sc.n();
  sgt_l = 0, sgt_r = q + 10;
  for (int i=1; i<=q; ++i) {
    int opt = sc.n(); 
    if (opt == 1) {
      int l=sc.n(), r=sc.n(), x=sc.n();
      opt2val[i] = x; ml[l].emplace_back(1, i), mr[r].emplace_back(1, i); }
    else if (opt == 2) {
      int l=sc.n(), r=sc.n();
      ml[l].push_back({2, i}), mr[r].emplace_back(2, i); }
    else if (opt == 3) {
      int s=sc.n(), k=sc.n();
      qs[s].emplace_back(3, i, k); }; }
} void solve() {
  memset(ans, 0xcf, sizeof(ans));
  for (int i=1; i<=n; ++i) {
    for (const Opt& x: ml[i]) {
      if (x.type == 1) { T.modify(x.id, sgt_r,  1, sgt_l, sgt_r, sgt_root); }
      if (x.type == 2) { T.modify(x.id, sgt_r, -1, sgt_l, sgt_r, sgt_root); } }

    for (const Opt& x: qs[i]) {
      int cur_top = T.query(x.id, x.id+1, sgt_l, sgt_r, sgt_root);
      int cur_buttom = T.query(sgt_l, x.id+1, sgt_l, sgt_r, sgt_root);
      int cur_size = cur_top - cur_buttom;
      if (cur_size < x.k) { ans[x.id] = -1; continue; }
      int find_size = cur_top - x.k;
      int l = 0, r = x.id - 1;
      while (l < r) { 
        int mid = (l + r + 1) / 2;
        if (T.query(mid, x.id, sgt_l, sgt_r, sgt_root) <= find_size) { l = mid; }
        else { r = mid - 1; } }
      ans[x.id] = opt2val[l + 1]; }

    for (const Opt& x: mr[i]) {
      if (x.type == 1) { T.modify(x.id, sgt_r, -1, sgt_l, sgt_r, sgt_root); }
      if (x.type == 2) { T.modify(x.id, sgt_r,  1, sgt_l, sgt_r, sgt_root); } } }

  for (int i=1; i<=q; ++i) {
    if (ans[i] == -1) { puts("Error"); }
    else if (ans[i] >= 0) { printf("%d\n", ans[i]); } }
}
