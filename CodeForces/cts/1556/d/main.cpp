#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

// #include "/home/jack/code/creats/Scanner.hpp"
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

int n, k;

void preInit() {  } 
void init() 
{
  std::cin >> n >> k;
} 

int query_and(int a, int b)
{
  a++, b++;
  std::cout << "and " << a << " " << b << std::endl;
  int r; std::cin >> r; return r;
}
int query_or(int a, int b)
{
  a++, b++;
  std::cout << "or " << a << " " << b << std::endl;
  int r; std::cin >> r; return r;
}

void solve() 
{
  std::vector<int> a(n, 0);
  int tand[3][3]; tand[0][1] = query_and(0, 1); tand[0][2] = query_and(0,2); tand[1][2] = query_and(1,2);
  int tor[3][3]; tor[0][1] = query_or(0, 1); tor[0][2] = query_or(0,2); tor[1][2] = query_or(1,2);

  for (int i = 0; i < 31; i++)
  {
    const int m = 1 << i;
    bool cand[3][3]; cand[0][1] = tand[0][1] & m; cand[0][2] = tand[0][2] & m; cand[1][2] = tand[1][2] & m;
    bool cor[3][3]; cor[0][1] = tor[0][1] & m; cor[0][2] = tor[0][2] & m; cor[1][2] = tor[1][2] & m;

    if (cor[0][1] == 0) { if (cor[0][2]) { a[2] |= m; } }
    else if (cand[0][1] == 1) { a[0] |= m; a[1] |= m; if (cand[0][2]) { a[2] |= m; } }
    else { 
      if ((int)cand[0][2] + (int)cor[0][2] < (int)cand[1][2] + (int)cor[1][2]) { a[1] |= m; if (cand[1][2]) { a[2] |= m; } }
      else { a[0] |= m; if (cand[0][2]) { a[2] |= m; } } }
  }

  for (int i = 3; i < n; i++)
    a[i] = (query_or(0, i) ^ a[0]) | query_and(0, i);
  see(a);

  std::sort(a.begin(), a.end());
  std::cout << "finish " << a[k - 1] << std::endl;
}
