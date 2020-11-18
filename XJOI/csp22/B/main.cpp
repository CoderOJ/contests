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

const int N = 1000005;
const int C = 11;

struct Point
{
  int x, y;
  Point (int x=0, int y=0) : x(x), y(y)
  { }
};

struct Line
{
  int k, b;
  Line (int k=0, int b=0) : k(k), b(b)
  { }

  int eval(int x)
  { return k * x + b; }

  double intersect(Line& B)
  {
    double dy = b - B.b;
    double dx = B.k - k;
    return dy / dx;
  }

  void log()
  {
    see(k, b);
  }

  static Line resolv(Point a, int k)
  { return Line(k, a.y - a.x * k); }
};

struct Lmin
{
  std::vector <Line> cand;
  int sz;
  Lmin () : sz(0)
  { }

  void insert(Line A)
  {
    while (sz > 0)
    {
      Line P  = cand[sz-1];
      if (P.k >= A.k) { sz--; cand.pop_back(); continue; }
      if (sz > 1) {
        Line PP = cand[sz-2];
        double int_pp = A.intersect( PP );
        double int_p  = A.intersect( P  );
        if (int_pp <= int_p) { sz--; cand.pop_back(); continue; }
      }
      break;
    }
    cand.push_back(A); sz++;
  }

  int get(int x)
  {
    if (sz == 0) { return 0x3f3f3f3f; }
    while (sz > 1)
    {
      Line P  = cand[sz-1];
      Line PP = cand[sz-2];
      if (P.eval(x) >= PP.eval(x)) { sz--; cand.pop_back(); continue; }
      break;
    }
    return cand[sz-1].eval(x);
  }
};

Lmin go[C][C];
int n, max_c;
int skip[N], cost[N];
int ans[N];

void preInit()
{ }

void init()
{
  n = sc.n(); max_c = sc.n();
  rep (i,n) { skip[i] = sc.n(); cost[i] = sc.n(); }
}

void solve()
{
  memset(ans, 0x3f, sizeof(ans));
  // see("Process begin");
  ans[0] = 0;
  rep (i,n)
  {
    repa (j,max_c) { checkMin(ans[i], go[j][i%j].get(i/j) ); }
    if (ans[i] != 0x3f3f3f3f)
    {
      // see(i, skip[i], cost[i], i/skip[i], ans[i]);
      Line A = Line::resolv( Point(i/skip[i],ans[i]), cost[i] );
      // A.log();
      go[ skip[i] ][ i%skip[i] ].insert( A );
    }
  }
  repa (j, max_c) { checkMin(ans[n], go[j][n%j].get(n/j) ); }
  repa (i,n) printf("%d ", (ans[i] == 0x3f3f3f3f) ? -1 : ans[i]);
}
