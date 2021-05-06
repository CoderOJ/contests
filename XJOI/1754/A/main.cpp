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

constexpr int N = 300005;
constexpr int MOD = 998244353;
constexpr int B = 61;

struct Trie {
  struct Node {
    Node *s[2];
    int size;
  } p[N * B];

  Node *root = p;
  Node *p_top = p + 1;

  void clear() {
    while (p_top != root) {
      *--p_top = {{nullptr, nullptr}, 0}; } 
    p_top = root + 1; }

  void insert(uint64_t a) {
    Node *p = root;
    for (int i=B; i>=0; i--) {
      int cur = (a >> i) & 1;
      p->size++;
      if (p->s[cur] == nullptr) { p->s[cur] = p_top++; }
      p = p->s[cur]; }
    p->size++; }

  int query(uint64_t a, uint64_t thr) {
    Node *p = root;
    int res = 0;
    for (int i=B; i>=0; i--) {
      if (p == nullptr) { break; }
      int cur = (a >> i) & 1;
      if (((thr>>i) & 1ull) == 0) {
        res += p->s[!cur] ? p->s[!cur]->size : 0; 
        p = p->s[cur]; }
      else { p = p->s[!cur]; } }
    if (p) { res += p->size; }
    return res; }
} T;

uint64_t a[N], x;
int n;

void preInit() { } void init() {
  sc.n(); n = sc.n(); x = (uint64_t)sc.nl();
  for (int i=0; i<n; ++i) a[i] = (uint64_t)sc.nl();
} void solve() {
  if (x == 0) { 
    int ans = 1;
    for (int i=0; i<n; ++i) ans = ans * 2 % MOD;
    printf("%d\n", (ans + MOD - 1) % MOD); return; }
  std::sort(a, a+n);
  int xlen = 0; while ((1ull << xlen) <= x) xlen++;
  uint64_t diff_mask = (~0ull) ^ ((1ull << xlen) - 1);
  long long ans = 1;
  for (int l=0,r=l; l < n; l = r) {
    while (r < n && (a[r] & diff_mask) == (a[l] & diff_mask)) { r++; }
    T.clear(); long long tot = r - l + 1; 
    for (int j=l; j<r; ++j) { tot += T.query(a[j], x); T.insert(a[j]); }
    ans = (1ll * ans * (tot % MOD)) % MOD; }
  printf("%lld\n", (ans + MOD - 1) % MOD); }
