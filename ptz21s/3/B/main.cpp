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
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 998244353;
using Int = Temps::Intm<MOD>;
constexpr int N = 100005;
constexpr int K = 6;

Int stir[K][K], binom[K][K];

void preInit() 
{ 
  stir[0][0] = 1;
  for (int i = 1; i < K; i++)
  {
    stir[i][0] = 0;
    for (int j = 1; j <= i; j++)
      stir[i][j] = stir[i - 1][j - 1] + stir[i - 1][j] * j;
  }
  for (int i = 0; i < K; i++)
  {
    binom[i][0] = 1;
    for (int j = 1; j <= i; j++)
      binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j];
  }
} 

int n, k, w;
int a[N];

struct kpow_t
{
  Int dwp[K];
  kpow_t() =default;
  kpow_t(Int x, Int t) {
    Int det = t;
    for (int i = 0; i < K; i++) { 
      dwp[i] = det; det *= (x - i); } }
  void log() { logArray(dwp, dwp + K); }

  void shift(Int det)
  {
    // if (dwp[0] != 0)  { see("shift", det); log(); }
    Int ndwp[K];
    for (int i = 0; i < K; i++) {
      Int bp = 1;
      for (int j = 0; j <= i; j++) {
        ndwp[i] += dwp[i - j] * bp * binom[i][j];
        bp *= (det - j); } }
    std::copy(ndwp, ndwp + K, dwp);
    // if (dwp[0] != 0)  { log(); }
  }
  Int get_pow(int x)
  {
    Int res = 0;
    for (int i = 0; i <= x; i++)
    {
      // see(stir[x][i], dwp[i]);
      res += stir[x][i] * dwp[i];
    }
    return res;
  }

};

struct kshift_t
{
  int val[K];
  kshift_t() =default;
  kshift_t(int x, int b, int t) {
    memset(val, 0, sizeof(val));
    for (int i = 0; i < w; i++) {
      val[i] = x % w;
      for (int j=0; j<k; j++) val[i] = val[i] * (b + i) % w; 
      val[i] *= t; } }

  void shift(int det) {
    int nval[K];
    for (int i = 0; i < w; i++)
      nval[i] = val[((i + det) % w + w) % w];
    std::copy(nval, nval + w, val); }

  void log() { logArray(val, val + K); }
};

struct node_t
{
  int cnt = 0;
  int shift = 0;
  kpow_t sum; 
  kshift_t rem; 

  void push_up(const node_t &a, const node_t &b) {
    cnt = a.cnt + b.cnt;
    for (int i = 0; i < K; i++) {
      sum.dwp[i] = a.sum.dwp[i] + b.sum.dwp[i];
      rem.val[i] = a.rem.val[i] + b.rem.val[i]; } }

  void push_modify(int val, int id, int det) {
    cnt += det;
    kpow_t sum_add(id, val * det); for (int i = 0; i < K; i++) sum.dwp[i] += sum_add.dwp[i]; 
    kshift_t rem_add(val, id, det); for (int i = 0; i < K; i++) rem.val[i] += rem_add.val[i]; 
    // see(val, id, det, cnt, shift);
    // sum_add.log(), sum.log();
    // rem_add.log(), rem.log();
  }

  void push_shift(int det) {
    shift += det, sum.shift(det), rem.shift(det); }
  void push_down(node_t &a, node_t &b) {
    if (shift) { a.push_shift(shift), b.push_shift(shift); shift = 0; } }

  Int get_ans()
  { 
    // see(sum.get_pow(k), rem.val[0]);
    return (sum.get_pow(k) - rem.val[0]) / Int(w); 
  }
};

node_t p[N * 4];

void sgt_shift(int u, int l, int r, int sl, int sr, int det)
{
  if (sl <= l && r <= sr) { p[u].push_shift(det); return; }
  p[u].push_down(p[u + u], p[u + u + 1]);
  int mid = (l + r) / 2;
  if (sl < mid) sgt_shift(u + u, l, mid, sl, sr, det);
  if (sr > mid) sgt_shift(u + u + 1, mid, r, sl, sr, det);
  p[u].push_up(p[u + u], p[u + u + 1]);
}

void sgt_modify(int u, int l, int r, int pos, int id, int det)
{
  if (r - l == 1) { p[u].push_modify(pos, id, det); return; }
  p[u].push_down(p[u + u], p[u + u + 1]);
  int mid = (l + r) / 2;
  if (pos < mid) sgt_modify(u + u, l, mid, pos, id, det);
  else sgt_modify(u + u + 1, mid, r, pos, id, det);
  p[u].push_up(p[u + u], p[u + u + 1]);
}

int sgt_getcnt(int u, int l, int r, int sl, int sr)
{
  if (sl <= l && r <= sr) { return p[u].cnt; }
  p[u].push_down(p[u + u], p[u + u + 1]);
  int mid = (l + r) / 2;
  return (sl < mid ? sgt_getcnt(u + u, l, mid, sl, sr) : 0) +
         (sr > mid ? sgt_getcnt(u + u + 1, mid, r, sl, sr) : 0);
}

int gu, gl, gr;

void init() 
{
  n = sc.n(); k = sc.n(); w = sc.n();
  for (int i = 0; i < n; i++) a[i] = sc.n();
  gu = 1, gl = 0, gr = N - 2;
} 

void solve() 
{
  auto erase = [](int x)
  {
    int prefix_cnt = sgt_getcnt(gu, gl, gr, 0, x);
    sgt_modify(gu, gl, gr, x, prefix_cnt + 1, -1);
    sgt_shift(gu, gl, gr, x, gr, -1); 
  };

  auto insert = [](int x)
  {
    int prefix_cnt = sgt_getcnt(gu, gl, gr, 0, x);
    sgt_shift(gu, gl, gr, x, gr, 1);
    sgt_modify(gu, gl, gr, x, prefix_cnt + 1, 1);
  };

  for (int i = 0; i < n; i++) 
  {
    insert(a[i]);
  }

  int q = sc.n();
  for (int i = 0; i < q; i++)
  {
    int id = sc.n() - 1, val = sc.n();
    erase(a[id]); a[id] = val; insert(a[id]);
    std::cout << p[gu].get_ans() << std::endl;
  }
}
