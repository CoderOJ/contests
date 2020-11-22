#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

const int N = 1005;
typedef Intm::Intm Int;
int n, p, m;
Int a[N], x;

Int s[N][N];
void
initSt()
{
  s[0][0] = 1;
  for (int i = 1; i < N; ++i) {
    s[i][0] = 0;
    for (int j = 1; j <= i; ++j) {
      s[i][j] = s[i - 1][j - 1] + Int(j) * s[i - 1][j];
    }
  }
}

Int pow_x[N], pow_xp[N];
void
initPow()
{
  pow_x[0] = 1;
  pow_xp[0] = (x+Int(1)).pow(n-m);
  for (int i = 1; i <= m; ++i) {
    pow_x[i] = pow_x[i - 1] * x;
    pow_xp[i] = pow_xp[i - 1] * (x + Int(1));
  }
}

Int n_ds[N];
void
initNDs()
{
  n_ds[0] = 1;
  for (int i = 1; i <= m; ++i) {
    n_ds[i] = n_ds[i - 1] * Int(n - i + 1);
  }
}

void
preInit()
{}

void
init()
{
  n = sc.n();
  x = sc.n();
  p = sc.n();
  m = sc.n();
  for (int i = 0; i <= m; ++i)
    a[i] = sc.n();
  Int::setMod(p);
  initSt();
  initPow();
  initNDs();
}

Int
getCoe(int i)
{
  Int res = 0;
  for (int j = 0; j <= i; ++j) {
    see(s[i][j], n_ds[j], pow_x[j], pow_xp[m-j]);
    res += s[i][j] * n_ds[j] * pow_x[j] * pow_xp[m - j];
  }
  see(i, res);
  return res;
}

void
solve()
{
  Int ans = 0;
  for (int i = 0; i <= m; ++i) {
    ans += a[i] * getCoe(i);
  }
  printf("%d\n", static_cast<int>(ans));
}
