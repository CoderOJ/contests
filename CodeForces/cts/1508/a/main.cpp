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

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 500005;
char a[N], b[N], c[N];
char ans[N];
int n;

bool gen(char *a, char *b, char c)
{
  int used = 0;
  int ap = 0, bp = 0;
  while (ap < 2*n && bp < 2*n)
  {
    int af=ap; while (af < n*2 && a[af] != c) af++;
    int bf=bp; while (bf < n*2 && b[bf] != c) bf++;
    int len = std::max(af-ap, bf-bp);
    for (int i=0; i<len; ++i) ans[used++] = (c ^ 1);
    if (af != 2*n || bf != 2*n) ans[used++] = c;
    ap = af+1; bp = bf+1;
  }
  while (ap<2*n) ans[used++] = a[ap++];
  while (bp<2*n) ans[used++] = b[bp++];
  if (used > 3*n) return false;
  see(a,b,c);
  while (used < 3*n) ans[used++] = '0';
  ans[3*n] = '\0';
  puts(ans);
  return true;
}

void preInit() { } void init() {
  n = sc.n();
  sc.next(a); sc.next(b); sc.next(c);
} void solve() {
  if (gen(a,b,'0')) return;
  if (gen(a,c,'0')) return;
  if (gen(b,a,'0')) return;
  if (gen(b,c,'0')) return;
  if (gen(c,a,'0')) return;
  if (gen(c,b,'0')) return;
  if (gen(a,b,'1')) return;
  if (gen(a,c,'1')) return;
  if (gen(b,a,'1')) return;
  if (gen(b,c,'1')) return;
  if (gen(c,a,'1')) return;
  if (gen(c,b,'1')) return;
}
