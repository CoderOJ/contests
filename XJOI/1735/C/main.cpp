#define __AVX__ 1
#define __AVX2__ 1
#define __SSE__ 1
#define __SSE2__ 1
#define __SSE2_MATH__ 1
#define __SSE3__ 1
#define __SSE4_1__ 1
#define __SSE4_2__ 1
#define __SSE_MATH__ 1
#define __SSSE3__ 1
#ifndef __LOCALE__
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#endif
#include <immintrin.h>
#include <emmintrin.h>

#include "/home/jack/code/creats/Scanner.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 150500;
int n, q;
unsigned int m;

__m256i a[N / 8];
unsigned int *ra = (unsigned int*)&a;

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); q = sc.n();
  for (int i=0; i<n; ++i) ra[i] = sc.n();
  while (!(n & 7)) n++;
} void solve() {
  __m256i sub_mod = _mm256_set1_epi32((int)m);
  __m256i sub_cmp = _mm256_set1_epi32((int)m - 1);
  while (q--) {
    int opt = sc.n();
    if (opt == 1) {
      int l = sc.n()-1, r = sc.n(), x = sc.n();
      if (r - l < 16) {
        for (int i=l; i<r; ++i) { ra[i] += x; if (ra[i] >= m) { ra[i] -= m; } } }
      else {
        while (l & 7) { ra[l] += x; if (ra[l] >= m) { ra[l] -= m; } l++; }
        while (r & 7) { r--; ra[r] += x; if (ra[r] >= m) { ra[r] -= m; } }
        int pl = l / 8, pr = r / 8;
        __m256i add = _mm256_set1_epi32(x);
        for (int i=pl; i<pr; ++i) {
          a[i] = _mm256_add_epi32(a[i], add);
          __m256i condition = _mm256_cmpgt_epi32(a[i], sub_cmp);
          __m256i sub = _mm256_and_si256(condition, sub_mod);
          a[i] = _mm256_sub_epi32(a[i], sub); } } }
    else {
      int l = sc.n()-1, r = sc.n();
      long long lsum = 0;
      if (r - l < 16) {
        for (int i=l; i<r; ++i) { lsum += ra[i]; } }
      else {
        while (l & 7) { lsum += ra[l]; l++; }
        while (r & 7) { r--; lsum += ra[r]; }
        int pl = l / 8, pr = r / 8;
        __m256i sum = _mm256_set1_epi32(0);
        for (int i=pl; i<pr; ++i) {
          sum = _mm256_add_epi32(sum, a[i]); }
        unsigned int *rsum = (unsigned int*)&sum;
        lsum += (long long)(rsum[0]) + (long long)(rsum[1]);
        lsum += (long long)(rsum[2]) + (long long)(rsum[3]);
        lsum += (long long)(rsum[4]) + (long long)(rsum[5]);
        lsum += (long long)(rsum[6]) + (long long)(rsum[7]); }
      printf("%lld\n", lsum); } }
}
