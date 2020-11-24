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
using namespace Polys;

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

void
preInit()
{}

void
init()
{}

void
solve()
{
  int _n = sc.n();
  int _k = sc.n();
  int k = std::max(3, _k+1);
  Poly Delta(k);
  Delta[0] = 1;
  Delta[1] = 6;
  Delta[2] = 1;
  Delta = Delta.sqrt();
  Poly Z = Delta;
  Z[0] += Int(1);
  Z[1] += Int(1);
  Z *= Int(1) / Int(2);
  int n = (_n+1) % MOD;
  Z = Z.pow(n,n);
  Z *= Delta.inv();
  repa (i,_k) {
    printf("%u ", i <= _n ? static_cast<unsigned>(Z[i]) : 0);
  }
}
