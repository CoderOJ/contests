#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"

#define POLY_H_MOD 167772161
#define POLY_H_MOD_W 3
#include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

using namespace Polys;

void preInit()
{

}

void init()
{

}

Poly shift(Poly& _A, int k)
{
  int n = 1 << _A.n;
  Poly A = _A;
  Int fac = 1;
  for (int i = 1; i < n; ++i)
  {
    fac *= Int(i);
    A[i] *= fac;
  }
  Poly B(n);
  Pre::Inv.require(n);
  Int fac_i = 1;
  Int k_pow = 1;
  B[0] = 1;
  for (int i = 1; i < n; ++i)
  {
    k_pow *= Int(k);
    fac_i *= Pre::Inv.inv[i];
    B[i] = k_pow * fac_i;
  }
  std::reverse(B.a, B.a+n);
  A *= B; 
  for (int i = 0; i < n; ++i)
    A[i] = A[i + n - 1];
  A.trim(n);
  fac_i = 1;
  for (int i = 1; i < n; ++ i)
  {
    fac_i *= Pre::Inv.inv[i];
    A[i] *= fac_i;
  }
  return A;
}

Poly get(int n)
{
  if (n == 1) {
    Poly R(2);
    R[0] = 0;
    R[1] = 1;
    return R;
  }
  int half_n = n / 2;
  Poly A = get(half_n);
  Poly B = shift(A, half_n);
  A *= B;
  if (n & 1) {
    Poly C = A;
    for (int i = 0; i<=n; ++i)
      A[i] *= Int(n-1);
    for (int i = 0; i<n; ++i)
      A[i+1] += C[i];
  }
  A.trim(n+1);
  return A;
}

void solve()
{
  int n = sc.n();
  Poly R = get(n);
  for (int i = 0; i<=n; ++i)
    printf("%u ", static_cast<unsigned>(R[i]));
}
