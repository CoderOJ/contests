#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/Vector.h"
#include "/home/jack/code/creats/util.h"

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

constexpr int N = 525050;
constexpr int B = 21;

struct Trie {
  struct Node {
    Node *s[2] = {nullptr,nullptr};
    int size = 0;
    ~Node() { delete s[0]; delete s[1]; } };
  Node *root = new Node();
  int xor_sum = 0;

  Trie() {}
  Trie(const Trie&) =delete;
  Trie(Trie&&) =delete;
  Trie& operator= (const Trie& rhs)=delete;
  Trie& operator= (Trie&& rhs) {
    delete root;
    root = rhs.root; xor_sum = rhs.xor_sum;
    rhs.root = nullptr; return *this; }

  void insert(int x) {
    xor_sum ^= x;
    Node *pos = root; 
    pos->size++;
    for (int i=0; i<B; ++i) {
      int tmp = (x >> i) & 1;
      if (pos->s[tmp] == nullptr) {
        pos->s[tmp] = new Node(); }
      pos = pos->s[tmp]; pos->size++; } }
  
  void inc() {
    Node *pos = root;
    int wei = 0;
    while (pos) {
      xor_sum ^= (pos->size & 1) << wei;
      std::swap(pos->s[0], pos->s[1]); 
      pos = pos->s[0]; wei++; } }

  static void _mergeTo(const Node *u, Trie& T, int pre_sum, int pre_wei) {
    if (pre_wei == B) {
      for (int _=0; _<u->size; ++_) {
        T.insert(pre_sum); } }
    if (u->s[0]) { _mergeTo(u->s[0], T, pre_sum, pre_wei+1); }
    if (u->s[1]) { _mergeTo(u->s[1], T, pre_sum + (1<<pre_wei), pre_wei+1); } }
  
  void merge(const Trie& rhs) {
    _mergeTo(rhs.root, *this, 0, 0); }

  ~Trie() { delete root; }
} T[N];

Temps::Vector<int> e[N];
int val[N], ws[N], size[N];
int n;

long long ans = 0;

void dfs1(int u) {
  size[u] = 1; int max_s = 0;
  for (int v: e[u]) { 
    dfs1(v);  size[u] += size[v];
    if (checkMax(max_s, size[v])) { ws[u] = v; } }
}

void dfs2(int u) {
  for (int v: e[u]) { dfs2(v); }
  if (ws[u]) { T[u] = std::move(T[ws[u]]); } 
  for (int v: e[u]) { if (v!=ws[u]) { T[u].merge(T[v]); } }
  T[u].inc(); 
  T[u].insert(val[u]);
  ans += T[u].xor_sum; }

void preInit() { } void init() {
  n = sc.n();
  for (int i: range(1,n+1)) { val[i] = sc.n(); }
  for (int i: range(2,n+1)) { e[sc.n()].push_back(i); }
} void solve() {
  dfs1(1); dfs2(1);
  printf("%lld\n", ans);
}
