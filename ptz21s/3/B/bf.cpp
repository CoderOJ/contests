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
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

using Int = Temps::Intm<>;
void preInit() {  }  void init() { } 

int n, k, w;

Int calc(int *a)
{
  std::vector<int> b(a, a + n);
  std::sort(b.begin(), b.end());
  Int ansr = 0, anss = 0;
  for (int i = 0; i < n; i++)
  {
    Int cur = b[i];
    for (int j = 0; j < k; j++) cur *= (i+1);
    int cus = b[i] % w;
    for (int j = 0; j < k; j++) cus = cus * (i+1) % w;
    ansr += cur, anss += cus;
  }
  see(ansr, anss);
  return (ansr - anss) / w;
}

int a[100005];

void solve() 
{
  n = sc.n(); k = sc.n(); w = sc.n();
  for (int i = 0; i < n; i++) a[i] = sc.n();
  int q = sc.n();
  for (int i = 0; i < q; i++)
  {
    int id = sc.n() - 1, val = sc.n();
    a[id] = val;
    std::cout << calc(a) << std::endl;
  }
}
