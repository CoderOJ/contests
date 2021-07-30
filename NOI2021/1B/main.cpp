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


#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 998244353;
constexpr int N = 200;
inline void chk_sub(int &a) { a = (a >= MOD ? a-MOD : a); }
inline void chk_add(int &a) { a = (a < 0 ? a+MOD : a); }
int nn;

int power(int a, int b) { 
  int r = 1;
  for (; b; b >>= 1) {
    if (b & 1) r = 1ll * r * a % MOD;
    a = 1ll * a * a % MOD; }
  return r; }
int inv(int a) { return power(a, MOD-2); }

struct Matrix {
  int a[N][N]; 
  Matrix() { memset(a, 0, sizeof(a)); }
  int* operator[] (int id) { return a[id]; }
  const int* operator[] (int id) const { return a[id]; }
  Matrix operator* (const Matrix &rhs) const {
    Matrix C;
    for (int i=0; i<nn; i++) 
      for (int k=0; k<nn; k++) 
        for (int j=0; j<nn; j++) 
          chk_sub(C[i][j] += a[i][k] * rhs[k][j]);
    return C; }
  int det(int n) {
    int ans = 1;
    for (int i=0; i<n; i++) {
      int p=-1; for (int j=i; j<n; j++) if (a[j][i]) { p = j; break; }
      if (p == -1) return 0;
      if (p != i) { for (int j=i; j<n; j++) std::swap(a[i][j], a[p][j]); ans=-ans; }
      for (int j=i+1; j<n; j++) {
        int t = 1ll * a[j][i] * inv(a[i][i]) % MOD;
        for (int k=i; k<n; k++) { 
          chk_add(a[j][k] -= 1ll * a[i][k] * t % MOD); } } }
    for (int i=0; i<n; i++) ans = 1ll * ans * a[i][i] % MOD; chk_add(ans);
    return ans; }
};

int k, n[N], m[N];

void preInit() {  } 
void init() 
{
  k = sc.n();
  for (int i=0; i<k; i++) n[i] = sc.n();
  nn = *std::max_element(n, n + k);
  for (int i=0; i+1<k; i++) m[i] = sc.n();
} 

void solve() 
{
  Matrix a;
  for (int i=0; i<n[0]; i++) a[i][i] = 1;
  for (int i=0; i+1<k; i++) {
    Matrix b;
    for (int j=0; j<m[i]; j++) {
      int u=sc.n()-1, v=sc.n()-1; b[u][v] = 1; }
    a = a * b; }
  printf("%d\n", a.det(n[0]));
}
