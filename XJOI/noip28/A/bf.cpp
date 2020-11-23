#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/


void preInit()
{

}

const int N = 805;
int a[N][N], n, m;

void init()
{
  n = sc.n(); m = sc.n();
  rep (i,n) rep (j,m) a[i][j] = sc.n();
}

int qMin(int ux, int uy, int vx, int vy) {
  int res = 0x3f3f3f3f;
  repi (i,ux,vx) repi (j,uy,vy) checkMin(res, a[i][j]);
  return res;
}

int qMax(int ux, int uy, int vx, int vy) {
  int res = 0;
  repi (i,ux,vx) repi (j,uy,vy) checkMax(res, a[i][j]);
  return res;
}

int qSum(int ux, int uy, int vx, int vy) {
  int res = 0;
  repi (i,ux,vx) repi (j,uy,vy) res += a[i][j];
  return res;
}

void solve()
{
  int q=sc.n();
  while (q--) {
    char opt;
    int ux, uy, vx, vy;
    sc.nextChar();
    opt = sc.nextChar();
    sc.nextChar();
    ux = sc.n();
    uy = sc.n();
    vx = sc.n();
    vy = sc.n();
    if (opt == 'U') {
      printf("%d\n", qSum(ux, uy, vx, vy));
    } else if (opt == 'I') {
      printf("%d\n", qMin(ux, uy, vx, vy));
    } else {
      printf("%d\n", qMax(ux, uy, vx, vy));
    }
  }
}
