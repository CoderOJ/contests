#pragma GCC optimize("Ofast")
#pragma GCC target("avx", "avx2")
#include <immintrin.h>

#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 300005;
constexpr int M = 7;
std::vector<int> e[N];
int n, m, w2id[N], w[N];

constexpr int gu = 1, gl = 1; int gr;

#pragma pack(1)
struct STree {
  struct Node {
    // in this case, (_cnt + 6) is 32-bits aligned
    __attribute__ ((aligned(1))) int min = 0;
    __attribute__ ((aligned(1))) int add = 0; 
    __attribute__ ((aligned(1))) int _cnt[M + 7] = {0};
    void push_add(int delta) { min += delta; add += delta; }
    void push_up(const Node *a, const Node *b);
    void push_down(Node *a, Node *b) { 
      a->push_add(add); b->push_add(add); add=0; }
  } __attribute__ ((aligned(64)));
  Node p[N * 4];

  void init(int u, int l, int r) {
    if (r - l == 1) { p[u].min = 1; p[u]._cnt[6] = 1; return; }
    int mid = (l + r) / 2; init(u + u, l, mid); init(u + u + 1, mid, r);
    p[u].push_up(&p[u + u], &p[u + u + 1]); }

  void modify(int u, int l, int r, int ml, int mr, int det) {
    if (ml <= l && r <= mr) { p[u].push_add(det); return; } 
    p[u].push_down(&p[u + u], &p[u + u + 1]); int mid = (l + r) / 2;
    if (ml < mid) modify(u + u, l, mid, ml, mr, det);
    if (mr > mid) modify(u + u + 1, mid, r, ml, mr, det);
    p[u].push_up(&p[u + u], &p[u + u + 1]); }
} __attribute__ ((aligned(64)));

STree T;

void STree::Node::push_up(const Node *a, const Node *b) {
  if (a->min > b->min) { std::swap(a, b); }
  int d = b->min - a->min; min = a->min;
  if (d < M) 
  {
    // equivalent code:
    // for (int i=0; i<8; i++) 
    //   cnt[i] = a->cnt[i] + b->cnt[i - d];
    //
    // rewrite because compiler does not know (this, a, b) are always pair-wise distinct
    _mm256_store_si256(
      reinterpret_cast<__m256i*>(_cnt + 6),
      _mm256_add_epi32(
        _mm256_load_si256(reinterpret_cast<const __m256i*>(a->_cnt + 6)),
        // notice: (b->_cnt + 6 -d) is not aligned
        _mm256_loadu_si256(reinterpret_cast<const __m256i_u*>(b->_cnt + 6 - d))));
  }
  else 
  {
    // equivalent code:
    // memcpy(_cnt + 6, a->_cnt + 6, sizeof(int) * 8); 
    //
    // rewrite because compiler does not know (_cnt + 6) is 32-bit aligned
    _mm256_store_si256(
      reinterpret_cast<__m256i*>(_cnt + 6),
      _mm256_load_si256(reinterpret_cast<const __m256i*>(a->_cnt + 6)));
  }
}

void preInit() {  } 
void init() 
{
  n = sc.n(); m = 2; gr = n + 1;
  T.init(gu, gl, gr);
  for (int i=1; i<=n; i++) w2id[w[i] = sc.n()] = i;
  for (int i=1; i<n; i++) { e[i].push_back(i+1); e[i+1].push_back(i); }
} 

void solve() 
{
  long long ans = 0;
  for (int i=1; i<=n; i++) { int u = w2id[i]; 
    if (i != 1) T.modify(gu, gl, gr, gl, i, 1);
    for (int v: e[u]) if (w[v] < w[u]) {
      T.modify(gu, gl, gr, gl, w[v] + 1, -1); }
    for (int i=0; i<m; i++) ans += T.p[gu]._cnt[6 + i];
    ans -= (n - i); }
  printf("%lld\n", ans - n);
}
