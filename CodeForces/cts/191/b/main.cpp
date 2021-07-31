#include "/home/jack/code/creats/gpl.hpp"

#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
#define int long long

/** My code begins here **/

constexpr int N = 100005;
std::pair<int,int> a[N];
int n, k, t;

void preInit() {  } 
void init() 
{
  n = sc.n(); k = sc.n(); t = sc.nl();
  for (int i=0; i<n; i++) a[i] = std::make_pair(sc.n(), i);
} 

template <class InputIterator, class Tp>
auto accumulate(InputIterator l, InputIterator r, Tp init) -> Tp {
  while (l != r) { init += *l; l++; } return init; }

void solve() 
{
  std::sort(a, a + n - 1, [](auto x, auto y) { return x.first > y.first; });
  auto pre = ::accumulate(a, a + k - 1, std::make_pair(0ll,0ll));
  int rid = -1; for (int i=k-1; i<n-1; i++) if ((pre + a[i]).first > t) rid = i;
  if (rid == -1) { printf("%lld\n", n); return; }
  printf("%lld\n", std::min_element(a, a+rid+1, [](auto x, auto y) { return x.second < y.second; })->second + 1);
}
