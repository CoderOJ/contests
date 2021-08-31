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

constexpr int N = 100005;
int a[N], n;

void preInit() {  } 
void init() 
{
  n = sc.n();
  for (int i = 0; i < n; i++) a[i] = sc.n() % 2;
} 

void solve() 
{
  int cnt[2] = {0,0};
  for (int i = 0; i < n; i++) cnt[a[i]]++;
  if (std::abs(cnt[0] - cnt[1]) > 1) { puts("-1"); return; }

  long long ptot[2] = {0,0};
  for (int i = 0; i < n; i++) ptot[a[i]] += i;

  if (n % 2 == 0)
  {
    int p1 = 0, p2 = 1;
    long long ans1 = 0, ans2 = 0;
    for (int i = 0; i < n; i++)
      if (a[i] == 1)
      {
        ans1 += std::abs(p1 - i); p1 += 2; 
        ans2 += std::abs(p2 - i); p2 += 2;
      }
    printf("%lld\n", std::min(ans1, ans2));
  }
  else
  {
    int max_id = cnt[0] > cnt[1] ? 0 : 1;
    int p = 0; long long ans = 0;
    for (int i = 0; i < n; i++)
      if (a[i] == max_id)
      {
        ans += std::abs(p - i);  p += 2;
      }
    printf("%lld\n", ans);
  }
}
