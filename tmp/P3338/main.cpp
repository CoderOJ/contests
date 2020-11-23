#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
#include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

const int N = 100005;
double q[N];
int n;

void
preInit()
{}

void
init()
{
  n = sc.n();
  rep(i, n) q[i] = sc.nextDouble();
}

void
solve()
{
  Polys::CPoly A(n), B(n);
  rep(i, n) A[i].r = q[i];
  rep(i, n) B[i].r = q[n - i - 1];
  Polys::CPoly I(n + 1);
  I[0] = 0;
  repa(i, n) I[i] = 1.0 / i / i;
  int sz = 1 << (I.n+1);
  A.resize(sz);
  B.resize(sz);
  I.resize(sz);
  A.dft();
  B.dft();
  I.dft();
  rep(i,sz) {
    A[i] *= I[i];
    B[i] *= I[i];
  }
  A.idft();
  B.idft();
  rep (i,n) printf("%.6lf\n", A[i].r - B[n-i-1].r);
}
