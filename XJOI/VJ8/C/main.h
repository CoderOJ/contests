#include <bits/stdc++.h>
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/Intm.h"

constexpr int MOD = 1000000007;
constexpr int N = 156;

class Matrix {
public:
  unsigned int a[N][N];

  Matrix() : a{} {}
  Matrix(std::initializer_list<std::initializer_list<unsigned int>> _a) : a() {
    std::size_t _i=0;
    for (const auto& i: _a) { std::size_t _j=0;
      for (const auto& j: i) { a[_i][_j] = j; _j++; } _i++; } }
   inline unsigned int* operator[] (const int id) { return a[id]; }
   inline unsigned int const* operator[] (const int id) const { return a[id]; }
  
  Matrix operator* (const Matrix& B) const {
    Matrix C;
    unsigned long long Res[N][N] = {};
     unsigned long long H_MOD_ONCE = 1ull * MOD * MOD;
     unsigned long long H_MOD = (std::numeric_limits<unsigned long long>::max() / H_MOD_ONCE - 1) * H_MOD_ONCE;
    for (int i=0; i<N; ++i) for (int k=0; k<N; ++k) if (a[i][k]) for (int j=0; j<N; ++j) {
      Res[i][j] += static_cast<unsigned long long>(a[i][k]) * B[k][j]; 
      Res[i][j] -= Res[i][j] >= H_MOD ? H_MOD : 0; }
    for (int i=0; i<N; ++i) for (int j=0; j<N; ++j) {
      C[i][j] = Res[i][j] % MOD; }
    return C; }
  Matrix pow(long long k) const {
    Matrix R, A = *this;
    for (int i=0;i<N;++i) R[i][i]=1;
    for (;k;k>>=1) {
      if (k & 1) { R = R * A; }
      A = A * A; }
    return R; }
};

class ConversionMachine {

  std::map<std::pair<int,int>, int> id;
  int get_id(std::pair<int,int> u) {
    static int _id = 0;
    if (!id.count(u)) { id[u] = _id++; }
    return id[u]; }

  Matrix genMatrix(int n) {
    int tot = (n + 2) * (n + 1) / 2;
    Matrix R;
    for (int x=0;x<=n;++x) {
      for (int y=0;x+y<=n;++y) {
        R[tot + get_id({x,y})][tot + get_id({x,y})]++;
        if (x) { R[get_id({x-1,y+1})][get_id({x,y})] += x;        R[tot + get_id({x-1,y+1})][get_id({x,y})] += x; }
        if (y) { R[get_id({x,y-1})][get_id({x,y})] += y;          R[tot + get_id({x,y-1})][get_id({x,y})] += y;  }
        if (n-x-y) { R[get_id({x+1,y})][get_id({x,y})] += n-x-y;  R[tot + get_id({x+1,y})][get_id({x,y})] += n-x-y; } } }
    return R; }

public:
  int countAll (std::string s, std::string t, std::vector<int> cost, long long max_cost) {
    int n = s.size();
    int l_cost[3][3] = {
      {0,                cost[0],          cost[0]+cost[1]},
      {cost[1]+cost[2],  0,                cost[1]},
      {cost[2],          cost[2]+cost[0],  0}
    };

    int ori[3] = {0,0,0};
    for (int i=0;i<n;++i) {
      int dis = (s[i] + 3 - t[i]) % 3; ori[dis]++;
      max_cost -= l_cost[s[i] - 'a'][t[i] - 'a']; }

    if (max_cost < 0) { return 0; }
    int k = max_cost / (0ll + cost[0] + cost[1] + cost[2]);
    k = 3 * k + ori[1] * 2 + ori[2];

    int tot = (n+2) * (n+1) / 2;
    Matrix A; 
    A[get_id({ori[0], ori[1]})][0] = 1;
    A[tot + get_id({ori[0], ori[1]})][0] = 1;
    Matrix T = genMatrix(n);
    Matrix R = T.pow(k) * A;

    return R[tot + get_id({n,0})][0];
  }

};
