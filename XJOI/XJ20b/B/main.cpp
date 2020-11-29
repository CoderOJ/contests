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

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/


void preInit()
{

}

void init()
{

}

void solve()
{
  int T = sc.n();
  while (T--) {
    int n = sc.n();
    char st = 'a';
    while (n) {
      int x = 1;
      while ((x+1) * (x+2) / 2 <= n) { x++; }
      rep (i,x) putchar(st);
      st++;
      n -= x*(x+1)/2;
    }
    puts("");
  }
}
