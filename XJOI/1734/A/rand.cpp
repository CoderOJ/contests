#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

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

constexpr int N = 15;
int trans[N][N];
int n, q;

void randTrans() {
  static std::mt19937 rd(19260817);
  for (int i=0; i<=n; ++i)
    for (int j=0; j<n; ++j)
      trans[i][j] = rd() % (n + 1); }

int cnt[1 << 12][N];
bool valid() {
  memset(cnt, 0, sizeof(cnt));
  cnt[0][0] = 1;
  for (int i=0; i<(1<<n); ++i) {
    for (int j=0; j<=n; ++j)
      for (int k=0; k<n; ++k)
        if (!(i & (1 << k)))
          cnt[i | (1<<k)][trans[j][k]] += cnt[i][j]; }
  for (int i=0; i<(1<<n); ++i) {
    int sum = 0, popcnt = 0;
    for (int j=0; j<n; ++j) 
      if (i & (1 << j))
        sum += cnt[(1<<n)-1][j], popcnt++;
    if (sum == q) {
      printf("%d\n", n+1);
      for (int i=0; i<=n; ++i)
        for (int j=0; j<n; ++j)
          printf("%d%c", trans[i][j]+1, " \n"[j==n-1]);
      puts("1");
      printf("%d", popcnt);
      for (int j=0; j<n; ++j) 
        if (i & (1 << j)) 
          printf(" %d", j + 1);
      return true; } }
  return false; }


void preInit() { } void init() {
  n = sc.n(); q = sc.n();
} void solve() {
  do {
    randTrans(); 
  } while (!valid());
}
