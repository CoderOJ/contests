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

#ifndef M_PI
#define M_PI 3.1415926535897932384626
#endif

constexpr int N = 65536 * 2;
double a[N], ans[N];
int n;

typedef std::complex<double> Complex;
Complex A[N], B[N];

template <class T>
void butterfly(T a[], int len) {
  static int rev[N], rev_len=-1;
  if (rev_len != len) {
    rev_len = len; rev[0] = 0;
    for (int i=1;i<(1<<len);++i) {
      rev[i] = (rev[i>>1] >> 1) | ((i&1) << (len-1)); } } 
  for (int i=0; i<(1<<len);++i) if (i < rev[i]) { std::swap(a[i], a[rev[i]]); } }

void dft(Complex a[], int len) {
  static Complex w[N * 2]; 
  static int w_len = -1;
  if (w_len < len) {
    for (int i=w_len+1; i<=len; ++i) {
      int i_pow = 1 << i;
      double per_d = M_PI / (1 << i);
      for (int j=0;j<i_pow;++j) {
        w[i_pow + j] = Complex(cos(per_d * j), sin(per_d * j)); } }
    w_len = len; }
  
  butterfly(a, len);
  int len_pow = (1 << len);
  for (int l=1;l<len_pow; l<<=1) {
    for (int i=0; i<len_pow; i+=2*l) {
      for (int j=0; j<l; ++j) {
        Complex t = w[l+j] * a[i+l+j];
        a[i+l+j] = a[i+j] - t;
        a[i+j] += t; } } }
}

void idft(Complex a[], int len) {
  std::reverse(a+1, a+(1<<len));
  dft(a, len);
  for (int i=0;i<(1<<len);++i) {
    a[i] /= (1<<len); } }

void fpmul(Complex a[], Complex b[], int len) {
  dft(a, len); dft(b, len);
  for (int i=0;i<(1<<len);++i) {
    a[i] *= b[i]; }
  idft(a, len); }

void preInit() { } void init() {
  n = sc.n(); 
  repa (i,n) a[i] = sc.nextDouble();
  a[0] = a[n+1] = 0;
} void solve() {
  double pre = 1;
  repa (i,n) {
    pre *= a[i];
    A[i] = pre * (1 - a[i+1]);
    B[n-i] = (1 - a[i]) / pre;  }
  B[n] = 1;
  int len = 1;
  while ((1<<len) <= n+n) { len++; }
  fpmul(A, B, len);
  puts("0.000000000000");
  for (int i=n+1;i<n+n+1;++i) {
    double res = A[i].real();
    if (res < 0) { res = 0; }
    printf("%.12lf\n", res); }
}
