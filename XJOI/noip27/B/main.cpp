#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"

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

const int N = 100005;
char ctr[N];
int n, q;

void
preInit()
{}

std::pair<int, int>
emulate(int x, int y)
{
  rep(i, n)
  {
    int dx = 0, dy = 0;
    if (ctr[i] == 'U')
      dy = 1;
    if (ctr[i] == 'D')
      dy = -1;
    if (ctr[i] == 'L')
      dx = -1;
    if (ctr[i] == 'R')
      dx = 1;
    if (x + dx != 0 || y + dy != 0) {
      x += dx;
      y += dy;
    }
  }
  return std::pair<int, int>(x, y);
}

void
init()
{
  n = sc.n();
  rep(i, n) ctr[i] = sc.nextChar();
  q = sc.n();
}

namespace bf {
void
main()
{
  for (int i = 0; i < q; ++i) {
    int x = sc.nextInt(), y = sc.nextInt();
    auto res = emulate(x, y);
    printf("%d %d\n", res.first, res.second);
  }
}
} /* bf */

namespace lr {
bool
check()
{
  for (int i = 0; i < n; ++i)
    if (ctr[i] != 'L' && ctr[i] != 'R')
      return false;
  return true;
}
void
main()
{
  int pos = 0;
  int max_right = 0, max_left = 0;
  for (int i = 0; i < n; ++i) {
    pos += ctr[i] == 'L' ? -1 : 1;
    checkMin(max_left, pos);
    checkMax(max_right, pos);
  }
  auto le = emulate(-1, 0);
  auto ri = emulate(1, 0);
  for (int i = 0; i < q; ++i) {
    int x = sc.nextInt(), y = sc.nextInt();
    if (y != 0) {
      printf("%d %d\n", x + pos, y);
    } else if (x < 0 && x + max_right >= 0) {
      printf("%d %d\n", le.first, le.second);
    } else if (x > 0 && x + max_left <= 0) {
      printf("%d %d\n", ri.first, ri.second);
    } else {
      printf("%d %d\n", x + pos, y);
    }
  }
}
} /* lr */

void
solve()
{
  if (lr::check()) {
    lr::main();
  } else {
    bf::main();
  }
}
