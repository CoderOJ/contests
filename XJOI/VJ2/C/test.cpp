#include <cstdio>
#include <initializer_list>
#include <limits>

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
      Res[i][j] += static_cast<unsigned long long>(a[i][k]) * a[k][j]; 
      if (Res[i][j] >= H_MOD) { Res[i][j] -= H_MOD; } }
    for (int i=0; i<N; ++i) for (int j=0; j<N; ++j) {
      C[i][j] = Res[i][j] % MOD; }
    return C; }
  CXX14_CONSTEXPR Matrix pow(long long k) const {
    Matrix R{{1}}, A = *this;
    for (;k;k>>=1) {
      if (k & 1) { R = R * A; }
      A = A * A; }
    return R; }
};

CXX14_CONSTEXPR Matrix A{{2}};
CXX14_CONSTEXPR Matrix B = A.pow(1024);

int main() {
  printf("%u\n", B[0][0]);
}
