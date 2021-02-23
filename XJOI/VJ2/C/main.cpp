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

#include <iostream>
#include <cstdio>
#include <initializer_list>
#include <limits>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

#define CXX11_CONSTEXPR constexpr
#if __cplusplus >= 201402L
#define CXX14_CONSTEXPR constexpr
#else
#define CXX14_CONSTEXPR
#endif

CXX11_CONSTEXPR int MOD = 1000000007;
CXX11_CONSTEXPR int N = 95;

class Matrix {
protected:
  unsigned int a[N][N];

public:
  CXX11_CONSTEXPR Matrix() : a{} {}
  CXX14_CONSTEXPR Matrix(std::initializer_list<std::initializer_list<unsigned int>> _a) : a() {
    std::size_t _i=0;
    for (const auto& i: _a) { std::size_t _j=0;
      for (const auto& j: i) { a[_i][_j] = j; _j++; } _i++; } }
  CXX14_CONSTEXPR inline unsigned int* operator[] (const int id) { return a[id]; }
  CXX14_CONSTEXPR inline unsigned int const* operator[] (const int id) const { return a[id]; }
  
  CXX14_CONSTEXPR Matrix operator* (const Matrix& B) const {
    Matrix C;
    unsigned long long Res[N][N] = {};
    CXX14_CONSTEXPR unsigned long long H_MOD_ONCE = 1ull * MOD * MOD;
    CXX14_CONSTEXPR unsigned long long H_MOD = (std::numeric_limits<unsigned long long>::max() / H_MOD_ONCE - 1) * H_MOD_ONCE;
    for (int i=0; i<N; ++i) for (int k=0; k<N; ++k) if (a[i][k]) for (int j=0; j<N; ++j) {
      Res[i][j] += static_cast<unsigned long long>(a[i][k]) * B[k][j]; 
      Res[i][j] -= Res[i][j] >= H_MOD ? H_MOD : 0; }
    for (int i=0; i<N; ++i) for (int j=0; j<N; ++j) {
      C[i][j] = Res[i][j] % MOD; }
    return C; }
  CXX14_CONSTEXPR Matrix pow(long long k) const {
    Matrix R, A = *this;
    for (int i=0;i<N;++i) R[i][i]=1;
    for (;k;k>>=1) {
      if (k & 1) { R = R * A; }
      A = A * A; }
    return R; }
};

Matrix Transfer {
#include "./tab.csh"
};

void preInit() { } void init() {
} void solve() {
  printf("%u\n", Transfer.pow(sc.nl())[94][94]);
}
