#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

int area(int x1, int y1, int x2, int y2, int x3, int y3) {
  return (x1*y2 - x1*y3 - x2*y1 + x2*y3 + x3*y1 - x3*y2) & 3; }
int boundary(int x1, int y1, int x2, int y2) {
  return Temps::gcd(std::abs(x1 - x2), std::abs(y1 - y2)) % 4; }

constexpr int N = 6005;
int x[N], y[N], cnt[N][4][4][4], n;

void preInit() {  } 
void init() 
{
  n = sc.n();
  for (int i=0; i<n; i++) {
    x[i] = sc.n(); y[i] = sc.n(); }
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++) if (i != j) 
        cnt[i][x[j] & 3][y[j] & 3][boundary(x[i], y[i], x[j], y[j])]++;
} 

void solve() 
{
  long long eee_cnt = 0;
  long long ooe_cnt = 0;
  for (int i=0; i<n; i++)
    for (int b1=0; b1<4; b1++) 
      for (int b2=b1; b2<4; b2+=2)
        for (int s1=0; s1<16; s1++)
          for (int s2 = (b1==b2 ? s1 : 0); s2<16; s2++) {
            int x1 = s1 / 4, y1 = s1 % 4;
            int x2 = s2 / 4, y2 = s2 % 4;
            if (x1%2 != x2%2 || y1%2 != y2%2) continue;
            int b3 = (x1 == x2 && y1 == y2) ? 0 : 2;
            int pcnt = (x1 == x2 && y1 == y2 && b1 == b2) ? 
                       cnt[i][x1][y1][b1] * (cnt[i][x1][y1][b1] - 1) / 2 :
                       cnt[i][x1][y1][b1] * cnt[i][x2][y2][b2];
            if (pcnt) see(i, b1, b2, b3, x1, y1, x2, y2, pcnt);
            if (area(x[i], y[i], x1, y1, x2, y2) == (b1 + b2 + b3) % 4)
              (b1 % 2 ? ooe_cnt : eee_cnt) += pcnt; }
  see(ooe_cnt, eee_cnt);
  printf("%lld\n", ooe_cnt + eee_cnt / 3);
}
