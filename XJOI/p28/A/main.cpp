#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 1000000007;
typedef Intm::Intm<MOD> Int;

struct Poly : private std::vector<Int> {
  using std::vector<Int>::vector;
  using std::vector<Int>::operator[];
  Poly operator * (const Poly& B) const {
    Poly C(size() + B.size() - 1);
    for (std::size_t i = 0; i<size(); ++i) {
      for (std::size_t j = 0; j<B.size(); ++j) {
        C[i + j] += (*this)[i] * B[j]; } }
    return C; }
  Poly pow(int k) {
    Poly R(size()); R[0] = 1;
    Poly A = *this;
    for (;k;k>>=1) {
      if (k & 1) { 
        R = R * A; R.resize(size()); }
      A = A * A; A.resize(size()); }
    return R; }
};

int n, m, k;

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); k = sc.n();
} void solve() {
  n -= m;
  Poly A(k+1); A[0]=2; A[1]=2; A[2]=1; 
  Poly B(k+1); B[0]=1; B[1]=1;
  Poly C = A.pow(m) * B.pow(n);
  printf("%u\n", static_cast<unsigned>(C[k]));
}
