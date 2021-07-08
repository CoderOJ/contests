#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 1000005;
char s[N];
int aba[N];
int n, q;
bool all_ab = false;

void preInit() 
{ 

} 

void init() 
{
  n = sc.n();
  sc.next(s);
  q = sc.n();
  for (int i=1; i<n-1; ++i)
    aba[i] = s[i-1] == s[i+1];
  std::partial_sum(aba, aba+n, aba);

  if (*std::max_element(s, s + n) <= 'b')
    all_ab = true;
} 

int reach[N], vis[N];

void manacher(char *s, int n)
{
  for (int i=0, l=0, r=-1; i<n; ++i) {
    int k = (i > r) ? 0 : std::min(reach[l + r - i + 1], r - i + 1);
    while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k])
      k++;
    reach[i] = k;
    if (i + k - 1 > r) 
      r = i + k - 1, l = i - k; 
    // see(i, l, r);
    vis[l]++; vis[r + 1]--; }
}

void solve() 
{
  for (int i=0; i<q; ++i)
  {
    int l = sc.n() - 1, r = sc.n();
    if (aba[r - 2] != aba[l]) { putchar('1'); continue; }
    int n = r - l;

    // if (all_ab && n > 10) { putchar('1'); continue; }

    // see(l, r, n);
    std::fill(vis, vis + n + 1, 0);
    manacher(s + l, n);
    std::partial_sum(vis, vis + n, vis);
    // logArray(vis, vis + n);
    if (*std::min_element(vis, vis + n) == 0) putchar('0');
    else putchar('1');
  }
}
