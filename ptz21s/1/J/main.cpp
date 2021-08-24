#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

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


void preInit() {  } 
void init() { } 
void solve() 
{
  auto query1 = [](int x, int y, int z)
  {
    x++, y++, z++;
    printf("? 1 %d %d %d\n", x, y, z);
    fflush(stdout);
    int r; scanf("%d", &r);
    return r;
  };

  auto query2 = [](int x, int y)
  {
    x++, y++;
    printf("? 2 %d %d\n", x, y);
    fflush(stdout);
    int r; scanf("%d", &r);
    return r - 1;
  };

  int n; scanf("%d", &n);
  std::vector<int> ans(n);

  int a[] = { query1(1, 2, 3), query1(0, 2, 3), query1(0, 1, 3), query1(0, 1, 2) };
  std::vector<int> min2id, max2id;  
  int min_max = std::min({a[0], a[1], a[2], a[3]});
  int max_min = std::max({a[0], a[1], a[2], a[3]});
  for (int i = 0; i < 4; i++) 
    (a[i] == min_max ? max2id : min2id).push_back(i);

  for (int i = 4; i < n; i++)
  {
    int q[] = { query1(min2id[0], i, max2id[0]), query1(min2id[1], i, max2id[1]) };
    if (q[0] == q[1])
    {
      assert(min_max < q[0] && q[0] < max_min);
      ans[i] = q[0];
    }
    else if (std::max(q[0], q[1]) == min_max)
    {
      int rep_p = q[1] == min_max;
      ans[min2id[rep_p]] = min_max;
      min2id[rep_p] = i;
      min_max = q[!rep_p];
    }
    else
    {
      int rep_p = q[1] == max_min;
      ans[max2id[rep_p]] = max_min;
      max2id[rep_p] = i;
      max_min = q[!rep_p];
    }
  }

  ans[min2id[0]] = 2;
  ans[min2id[1]] = 2;
  ans[query2(min2id[0], min2id[1])] = 1;

  ans[max2id[0]] = n;
  ans[max2id[1]] = n;
  ans[query2(max2id[0], max2id[1])] = n - 1;

  std::cout << "! " << ans << std::endl;
}
