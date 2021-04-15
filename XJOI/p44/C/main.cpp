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

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 1600000;
char s[N], *sp=s;
int cnt[N], sa[N], rk[N*2], rk2[N], qs[N];
int n, q, p;

void append(int level) {
  if (level == 0) *sp++ = 'b';
  else if (level == 1) *sp++ = 'a';
  else { append(level - 1); append(level - 2); } }

void get_sa() {
  int m = 130;
  for (int i=0; i<n; ++i) { rk[i] = s[i]; cnt[rk[i]]++; }
  for (int i=1; i<m; ++i) { cnt[i] += cnt[i-1]; }
  for (int i=n-1; i>=0; --i) { sa[ --cnt[rk[i]] ] = i; }

  for (int len=1; len<n; len<<=1) {
    int top = 0;
    for (int i=n-1; i>=n-len; --i) rk2[top++] = i;
    for (int i=0; i<n; ++i) if (sa[i] >= len) rk2[top++] = sa[i]-len;
    memset(cnt, 0, sizeof(int) * m);
    for (int i=0; i<n; ++i) cnt[rk[i]]++;
    for (int i=1; i<m; ++i) cnt[i] += cnt[i-1];
    for (int i=n-1; i>=0; --i) sa[ --cnt[rk[rk2[i]]] ] = rk2[i];
    m = 0;
    rk2[ sa[0] ] = m++;
    for (int i=1; i<n; ++i) {
      bool reqNew = rk[sa[i-1]] != rk[sa[i]] || rk[sa[i-1]+len] != rk[sa[i]+len];
      rk2[sa[i]] = reqNew ? m++ : m-1; }
    memcpy(rk, rk2, sizeof(int) * n);
    if (m == n) { break; } } }

void preInit() { } void init() {
  n = sc.n(); q = sc.n();
  for (int i=0; i<q; ++i) qs[i] = sc.n();
  p = sc.n();
  append(n); n = sp - s;
} void solve() {
  get_sa(); 
  for (int i=0; i<q; ++i)
    printf("%d%c", (sa[qs[i] - 1] + 1) % p, " \n"[i==q-1]);
}
