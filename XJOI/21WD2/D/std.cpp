#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
const int N = 2010;
int a[N][N], n, x, tx, ty, ans;
int
ask(int x, int y, int f)
{
  if (f) swap(x, y);
  if (x < 1 || x > n || y < 1 || y > n) return -1e9;
  if (~a[x][y]) return a[x][y];

  int z;
  printf("? %d %d\n", x, y);
  fflush(stdout);
  scanf("%d", &z);

  if (f) swap(x, y);
  if (z > ans) ans = z, tx = x, ty = y;
  if (f) swap(x, y);
  a[x][y] = z;
  return z;
}
int
main()
{
  scanf("%d", &n);
  rep(i, 1, n) rep(j, 1, n) a[i][j] = -1;
  int l = 1, r = n, d = 1, u = n;
  while (1) {
    int mid = (l + r) >> 1;
    rep(i, d, u) ask(mid, i, x);
    rep(i, -1, 1) rep(j, -1, 1) ask(tx + i, ty + j, x);

    if (tx > mid) l = mid + 1;
    else r = mid - 1;

    if (l > r) break;
    swap(l, d), swap(r, u), swap(tx, ty);
    x ^= 1;
  }

  if (x) swap(tx, ty);
  printf("! %d %d\n", tx, ty);

  return 0;
}
