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


#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 15;
char a[N], s[N];

void preInit() {  } 
void init() 
{ sc.next(s); } 

int min_rounds() {
  int ar = 5, br = 5;
  int as = 0, bs = 0;
  for (int i=0; i<10; i++) {
    (i % 2 ? bs : as) += a[i] - '0';
    (i % 2 ? br : ar) --;
    if (as + ar < bs || bs + br < as)
      return i + 1; }
  return 10; }

void solve() 
{
  int ans = 10;
  for (int i=0; i<10; i++) 
    a[i] = s[i] == '?' ? (i % 2 ? '1' : '0') : s[i];
  checkMin(ans, min_rounds());
  for (int i=0; i<10; i++) 
    a[i] = s[i] == '?' ? (i % 2 ? '0' : '1') : s[i];
  checkMin(ans, min_rounds());
  printf("%d\n", ans);
}
