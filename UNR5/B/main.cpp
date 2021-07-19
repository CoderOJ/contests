#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

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

typedef __uint128_t u128;
inline u128 input() {
  static char buf[100];
  scanf ("%s", buf);
  u128 res = 0;
  for (int i = 0; buf[i]; ++i) {
    res = res << 4 | static_cast<u128>(buf[i] <= '9' ? buf[i] - '0' : buf[i] - 'a' + 10); }
  return res; }
inline void output (u128 res) {
  if (res >= 16)
    output (res / 16);
  putchar (res % 16 >= 10 ? 'a' + res % 16 - 10 : '0' + res % 16); }

constexpr u128 all = ((u128)(1) << 127) + (((u128)(1) << 127) - 1);
constexpr int N = 300005;
constexpr int B = 405;
u128 a[N], b[B];
int bel[N], ll[N];
int _pre[128][N], _suf[128][N], *pre[128], *suf[128];
int _pren0[N], _sufn0[N], *const pren0=_pren0+2, *const sufn0=_sufn0+2;
int n, q;

void preInit() 
{  
  for (int i=0; i<128; i++) { pre[i] = _pre[i]+2; suf[i] = _suf[i] + 2; }
  constexpr int LEN = N / B + 1;
  for (int i=0; i<N; i++) bel[i] = i / LEN;
  for (int i=0; i<B; i++) ll[i] = i * LEN;
}

void init()
{
  scanf("%d%d", &n, &q);
  for (int i=0; i<n; i++) b[bel[i]] += (a[i] = input());
  for (int b=0; b<128; b++) {
    const auto bit = static_cast<u128>(1) << b;
    pre[b][0] = -1; for (int i=1; i<n; i++) pre[b][i] = (a[i-1] & bit) ? i-1 : pre[b][i-1];
    suf[b][n-1] = n; for (int i=n-2; i>=0; i--) suf[b][i] = (a[i+1] & bit) ? i+1 : suf[b][i+1]; }
  pren0[0] = -1; for (int i=1; i<n; i++) pren0[i] = a[i-1] ? i-1 : pren0[i-1];
  sufn0[n-1] = n; for (int i=n-2; i>=0; i--) sufn0[i] = a[i+1] ? i+1 : sufn0[i+1];
  a[n] = all;
}

inline void erase(int *pre, int *suf, int x) {
  suf[pre[x]] = suf[x]; pre[suf[x]] = pre[x]; }
inline void modify(int i, u128 val) {
  b[bel[i]] += (val - a[i]); a[i] = val; }
inline int getfirst(int *next, int id, u128 test) {
  if (a[id] & test) { return id; }
  return next[id] = getfirst(next, next[id], test); }

void solve()
{
  if (n <= 3000 && q <= 3000) {
    while (q--) 
    {
      int opt; scanf("%d", &opt);
      if (opt == 1) {
        int l, r; scanf("%d%d", &l, &r); l--;
        u128 v = input(); if (v == 1) continue;
        for (int i=l; i<r; i++) { a[i] /= v; } }
      else if (opt == 2) {
        int l, r; scanf("%d%d", &l, &r); l--;
        u128 v = input(); 
        for (int i=l; i<r; i++) a[i] &= v; }
      else {
        int l, r; scanf("%d%d", &l, &r); l--;
        u128 ans = 0;
        for (int i=l; i<r; i++) ans += a[i]; 
        output(ans); puts(""); } 
    }
    return;
  }

  while (q--) 
  {
    int opt; scanf("%d", &opt);
    if (opt == 1) {
      int l, r; scanf("%d%d", &l, &r); l--;
      u128 v = input(); if (v == 1) continue;
      for (int i=getfirst(sufn0, l, all); i<r; i=sufn0[i]) {
        modify(i, a[i] / v); if (a[i] == 0) erase(pren0, sufn0, i); } }
    else if (opt == 2) {
      int l, r; scanf("%d%d", &l, &r); l--;
      u128 v = input(); 
      for (int b=0; b<128; b++) {
        const u128 cur = ((u128)(1) << b);
        if (v & cur) continue;
        for (int i=getfirst(suf[b], l, cur); i<r; i=suf[b][i]) {
          modify(i, a[i] ^ cur); erase(pre[b], suf[b], i); } } }
    else {
      int l, r; scanf("%d%d", &l, &r); l--;
      const int lb = bel[l], rb = bel[r];
      u128 ans = 0;
      if (lb == rb) { for (int i=l; i<r; i++) ans += a[i]; }
      else {
        for (int i=l; i<ll[lb+1]; i++) ans += a[i];
        for (int i=ll[rb]; i<r; i++) ans += a[i];
        for (int i=lb+1; i<rb; i++) ans += b[i]; }
      output(ans); puts(""); } 
  }
}
